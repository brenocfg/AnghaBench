#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mp_image {scalar_t__ imgfmt; } ;
struct mp_frame {scalar_t__ type; struct mp_image* data; } ;
struct mp_filter {struct deint_priv* priv; } ;
struct filter_opts {scalar_t__ deinterlace; } ;
struct TYPE_6__ {void* filter; struct mp_frame frame; } ;
struct deint_priv {scalar_t__ prev_imgfmt; scalar_t__ prev_setting; TYPE_1__ sub; TYPE_5__* opts; } ;
struct TYPE_7__ {struct filter_opts* opts; } ;

/* Variables and functions */
 scalar_t__ IMGFMT_CUDA ; 
 scalar_t__ IMGFMT_D3D11 ; 
 scalar_t__ IMGFMT_VAAPI ; 
 scalar_t__ IMGFMT_VDPAU ; 
 int /*<<< orphan*/  MP_ERR (struct mp_filter*,char*) ; 
 scalar_t__ MP_FRAME_VIDEO ; 
 int /*<<< orphan*/  MP_OUTPUT_CHAIN_VIDEO ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  m_config_cache_update (TYPE_5__*) ; 
 void* mp_create_user_filter (struct mp_filter*,int /*<<< orphan*/ ,char*,char**) ; 
 int /*<<< orphan*/  mp_filter_internal_mark_failed (struct mp_filter*) ; 
 scalar_t__ mp_frame_is_signaling (struct mp_frame) ; 
 int /*<<< orphan*/  mp_subfilter_continue (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_subfilter_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_subfilter_drain_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_subfilter_read (TYPE_1__*) ; 
 scalar_t__ mp_sws_supports_input (scalar_t__) ; 

__attribute__((used)) static void deint_process(struct mp_filter *f)
{
    struct deint_priv *p = f->priv;

    if (!mp_subfilter_read(&p->sub))
        return;

    struct mp_frame frame = p->sub.frame;

    if (mp_frame_is_signaling(frame)) {
        mp_subfilter_continue(&p->sub);
        return;
    }

    if (frame.type != MP_FRAME_VIDEO) {
        MP_ERR(f, "video input required!\n");
        mp_filter_internal_mark_failed(f);
        return;
    }

    m_config_cache_update(p->opts);
    struct filter_opts *opts = p->opts->opts;

    if (!opts->deinterlace)
        mp_subfilter_destroy(&p->sub);

    struct mp_image *img = frame.data;

    if (img->imgfmt == p->prev_imgfmt && p->prev_setting == opts->deinterlace) {
        mp_subfilter_continue(&p->sub);
        return;
    }

    if (!mp_subfilter_drain_destroy(&p->sub))
        return;

    assert(!p->sub.filter);

    p->prev_imgfmt = img->imgfmt;
    p->prev_setting = opts->deinterlace;
    if (!p->prev_setting) {
        mp_subfilter_continue(&p->sub);
        return;
    }

    if (img->imgfmt == IMGFMT_VDPAU) {
        char *args[] = {"deint", "yes", NULL};
        p->sub.filter =
            mp_create_user_filter(f, MP_OUTPUT_CHAIN_VIDEO, "vdpaupp", args);
    } else if (img->imgfmt == IMGFMT_VAAPI) {
        p->sub.filter =
            mp_create_user_filter(f, MP_OUTPUT_CHAIN_VIDEO, "vavpp", NULL);
    } else if (img->imgfmt == IMGFMT_D3D11) {
        p->sub.filter =
            mp_create_user_filter(f, MP_OUTPUT_CHAIN_VIDEO, "d3d11vpp", NULL);
    } else if (img->imgfmt == IMGFMT_CUDA) {
        char *args[] = {"mode", "send_field", NULL};
        p->sub.filter =
            mp_create_user_filter(f, MP_OUTPUT_CHAIN_VIDEO, "yadif_cuda", args);
    } else if (mp_sws_supports_input(img->imgfmt)) {
        char *args[] = {"mode", "send_field", NULL};
        p->sub.filter =
            mp_create_user_filter(f, MP_OUTPUT_CHAIN_VIDEO, "yadif", args);
    } else {
        MP_ERR(f, "no deinterlace filter available for this format\n");
        mp_subfilter_continue(&p->sub);
        return;
    }

    if (!p->sub.filter)
        MP_ERR(f, "creating deinterlacer failed\n");

    mp_subfilter_continue(&p->sub);
}