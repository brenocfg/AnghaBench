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
struct mp_filter {int /*<<< orphan*/ * ppins; struct deint_priv* priv; } ;
struct mp_autoconvert {struct mp_filter* f; } ;
struct filter_opts {scalar_t__ deinterlace; } ;
struct TYPE_6__ {struct mp_filter* filter; struct mp_frame frame; } ;
struct deint_priv {scalar_t__ prev_imgfmt; scalar_t__ prev_setting; TYPE_1__ sub; TYPE_5__* opts; } ;
struct TYPE_7__ {struct filter_opts* opts; } ;

/* Variables and functions */
 scalar_t__ IMGFMT_CUDA ; 
 scalar_t__ IMGFMT_D3D11 ; 
 scalar_t__ IMGFMT_VDPAU ; 
 int /*<<< orphan*/  MP_ERR (struct mp_filter*,char*,...) ; 
 scalar_t__ MP_FRAME_VIDEO ; 
 int /*<<< orphan*/  MP_OUTPUT_CHAIN_VIDEO ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  m_config_cache_update (TYPE_5__*) ; 
 int /*<<< orphan*/  mp_autoconvert_add_all_sw_imgfmts (struct mp_autoconvert*) ; 
 struct mp_autoconvert* mp_autoconvert_create (struct mp_filter*) ; 
 int /*<<< orphan*/  mp_autoconvert_probe_input_video (struct mp_autoconvert*,struct mp_image*) ; 
 struct mp_filter* mp_bidir_dummy_filter_create (struct mp_filter*) ; 
 int /*<<< orphan*/  mp_chain_filters (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mp_filter**,int) ; 
 void* mp_create_user_filter (struct mp_filter*,int /*<<< orphan*/ ,char*,char**) ; 
 int /*<<< orphan*/  mp_filter_internal_mark_failed (struct mp_filter*) ; 
 scalar_t__ mp_frame_is_signaling (struct mp_frame) ; 
 int /*<<< orphan*/  mp_imgfmt_to_name (scalar_t__) ; 
 int /*<<< orphan*/  mp_subfilter_continue (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_subfilter_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_subfilter_drain_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  mp_subfilter_read (TYPE_1__*) ; 
 int /*<<< orphan*/  talloc_free (struct mp_filter*) ; 

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
    } else if (img->imgfmt == IMGFMT_D3D11) {
        p->sub.filter =
            mp_create_user_filter(f, MP_OUTPUT_CHAIN_VIDEO, "d3d11vpp", NULL);
    } else if (img->imgfmt == IMGFMT_CUDA) {
        char *args[] = {"mode", "send_field", NULL};
        p->sub.filter =
            mp_create_user_filter(f, MP_OUTPUT_CHAIN_VIDEO, "yadif_cuda", args);
    } else {
        struct mp_filter *subf = mp_bidir_dummy_filter_create(f);
        struct mp_filter *filters[2] = {0};

        struct mp_autoconvert *ac = mp_autoconvert_create(subf);
        if (ac) {
            filters[0] = ac->f;
            // We know vf_yadif does not support hw inputs.
            mp_autoconvert_add_all_sw_imgfmts(ac);

            if (!mp_autoconvert_probe_input_video(ac, img)) {
                MP_ERR(f, "no deinterlace filter available for format %s\n",
                       mp_imgfmt_to_name(img->imgfmt));
                talloc_free(subf);
                mp_subfilter_continue(&p->sub);
                return;
            }
        }

        char *args[] = {"mode", "send_field", NULL};
        filters[1] =
            mp_create_user_filter(subf, MP_OUTPUT_CHAIN_VIDEO, "yadif", args);

        mp_chain_filters(subf->ppins[0], subf->ppins[1], filters, 2);
        p->sub.filter = subf;
    }

    if (!p->sub.filter)
        MP_ERR(f, "creating deinterlacer failed\n");

    mp_subfilter_continue(&p->sub);
}