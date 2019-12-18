#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mp_frame {scalar_t__ type; struct mp_image* data; } ;
struct TYPE_6__ {scalar_t__ filter; struct mp_frame frame; } ;
struct rotate_priv {int prev_rotate; scalar_t__ prev_imgfmt; int target_rotate; TYPE_2__ sub; } ;
struct mp_stream_info {scalar_t__ rotate90; } ;
struct TYPE_5__ {int rotate; } ;
struct mp_image {scalar_t__ imgfmt; TYPE_1__ params; } ;
struct mp_filter {struct rotate_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct mp_filter*,char*) ; 
 scalar_t__ MP_FRAME_VIDEO ; 
 int /*<<< orphan*/  MP_INFO (struct mp_filter*,char*) ; 
 int /*<<< orphan*/  MP_OUTPUT_CHAIN_VIDEO ; 
 int M_PI ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ mp_create_user_filter (struct mp_filter*,int /*<<< orphan*/ ,char*,char**) ; 
 struct mp_stream_info* mp_filter_find_stream_info (struct mp_filter*) ; 
 scalar_t__ mp_frame_is_signaling (struct mp_frame) ; 
 int /*<<< orphan*/  mp_subfilter_continue (TYPE_2__*) ; 
 int /*<<< orphan*/  mp_subfilter_drain_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  mp_subfilter_read (TYPE_2__*) ; 
 int /*<<< orphan*/  mp_sws_supports_input (scalar_t__) ; 
 char* mp_tprintf (int,char*,double) ; 

__attribute__((used)) static void rotate_process(struct mp_filter *f)
{
    struct rotate_priv *p = f->priv;

    if (!mp_subfilter_read(&p->sub))
        return;

    struct mp_frame frame = p->sub.frame;

    if (mp_frame_is_signaling(frame)) {
        mp_subfilter_continue(&p->sub);
        return;
    }

    if (frame.type != MP_FRAME_VIDEO) {
        MP_ERR(f, "video input required!\n");
        return;
    }

    struct mp_image *img = frame.data;

    if (img->params.rotate == p->prev_rotate &&
        img->imgfmt == p->prev_imgfmt)
    {
        img->params.rotate = p->target_rotate;
        mp_subfilter_continue(&p->sub);
        return;
    }

    if (!mp_subfilter_drain_destroy(&p->sub))
        return;

    assert(!p->sub.filter);

    int rotate = p->prev_rotate = img->params.rotate;
    p->target_rotate = rotate;
    p->prev_imgfmt = img->imgfmt;

    struct mp_stream_info *info = mp_filter_find_stream_info(f);
    if (rotate == 0 || (info && info->rotate90 && !(rotate % 90))) {
        mp_subfilter_continue(&p->sub);
        return;
    }

    if (!mp_sws_supports_input(img->imgfmt)) {
        MP_ERR(f, "Video rotation with this format not supported\n");
        mp_subfilter_continue(&p->sub);
        return;
    }

    double angle = rotate / 360.0 * M_PI * 2;
    char *args[] = {"angle", mp_tprintf(30, "%f", angle),
                    "ow", mp_tprintf(30, "rotw(%f)", angle),
                    "oh", mp_tprintf(30, "roth(%f)", angle),
                    NULL};
    p->sub.filter =
        mp_create_user_filter(f, MP_OUTPUT_CHAIN_VIDEO, "rotate", args);

    if (p->sub.filter) {
        MP_INFO(f, "Inserting rotation filter.\n");
        p->target_rotate = 0;
    } else {
        MP_ERR(f, "could not create rotation filter\n");
    }

    mp_subfilter_continue(&p->sub);
}