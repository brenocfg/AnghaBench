#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vf_format_opts {int gamma; double sig_peak; scalar_t__ rotate; scalar_t__ dw; scalar_t__ dh; scalar_t__ dar; int /*<<< orphan*/ * spherical_ref_angles; scalar_t__ spherical; scalar_t__ stereo_in; scalar_t__ chroma_location; scalar_t__ light; scalar_t__ primaries; scalar_t__ colorlevels; scalar_t__ colormatrix; scalar_t__ outfmt; } ;
struct priv {int /*<<< orphan*/  in_pin; struct vf_format_opts* opts; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ref_angles; scalar_t__ type; } ;
struct TYPE_5__ {int gamma; double sig_peak; scalar_t__ light; scalar_t__ primaries; scalar_t__ levels; scalar_t__ space; } ;
struct mp_image_params {scalar_t__ rotate; TYPE_2__ spherical; scalar_t__ stereo3d; scalar_t__ chroma_location; TYPE_1__ color; scalar_t__ imgfmt; } ;
struct mp_image {struct mp_image_params params; } ;
struct mp_frame {scalar_t__ type; struct mp_image* data; } ;
struct mp_filter {int /*<<< orphan*/ * ppins; struct priv* priv; } ;
typedef  enum mp_csp_trc { ____Placeholder_mp_csp_trc } mp_csp_trc ;
struct TYPE_7__ {scalar_t__ num; scalar_t__ den; } ;
typedef  TYPE_3__ AVRational ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ MP_CSP_LIGHT_AUTO ; 
 int /*<<< orphan*/  MP_ERR (struct mp_filter*,char*) ; 
 scalar_t__ MP_FRAME_VIDEO ; 
 TYPE_3__ av_d2q (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ isfinite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_filter_internal_mark_failed (struct mp_filter*) ; 
 scalar_t__ mp_frame_is_signaling (struct mp_frame) ; 
 int /*<<< orphan*/  mp_frame_unref (struct mp_frame*) ; 
 int /*<<< orphan*/  mp_image_params_get_dsize (struct mp_image_params*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  mp_image_params_guess_csp (struct mp_image_params*) ; 
 int /*<<< orphan*/  mp_image_params_set_dsize (struct mp_image_params*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mp_pin_can_transfer_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_pin_in_write (int /*<<< orphan*/ ,struct mp_frame) ; 
 struct mp_frame mp_pin_out_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vf_format_process(struct mp_filter *f)
{
    struct priv *priv = f->priv;
    struct vf_format_opts *p = priv->opts;

    if (!mp_pin_can_transfer_data(f->ppins[1], priv->in_pin))
        return;

    struct mp_frame frame = mp_pin_out_read(priv->in_pin);

    if (mp_frame_is_signaling(frame)) {
        mp_pin_in_write(f->ppins[1], frame);
        return;
    }
    if (frame.type != MP_FRAME_VIDEO) {
        MP_ERR(f, "unsupported frame type\n");
        mp_frame_unref(&frame);
        mp_filter_internal_mark_failed(f);
        return;
    }

    struct mp_image *img = frame.data;
    struct mp_image_params *out = &img->params;

    if (p->outfmt)
        out->imgfmt = p->outfmt;
    if (p->colormatrix)
        out->color.space = p->colormatrix;
    if (p->colorlevels)
        out->color.levels = p->colorlevels;
    if (p->primaries)
        out->color.primaries = p->primaries;
    if (p->gamma) {
        enum mp_csp_trc in_gamma = p->gamma;
        out->color.gamma = p->gamma;
        if (in_gamma != out->color.gamma) {
            // When changing the gamma function explicitly, also reset stuff
            // related to the gamma function since that information will almost
            // surely be false now and have to be re-inferred
            out->color.sig_peak = 0.0;
            out->color.light = MP_CSP_LIGHT_AUTO;
        }
    }
    if (p->sig_peak)
        out->color.sig_peak = p->sig_peak;
    if (p->light)
        out->color.light = p->light;
    if (p->chroma_location)
        out->chroma_location = p->chroma_location;
    if (p->stereo_in)
        out->stereo3d = p->stereo_in;
    if (p->rotate >= 0)
        out->rotate = p->rotate;

    AVRational dsize;
    mp_image_params_get_dsize(out, &dsize.num, &dsize.den);
    if (p->dw > 0)
        dsize.num = p->dw;
    if (p->dh > 0)
        dsize.den = p->dh;
    if (p->dar > 0)
        dsize = av_d2q(p->dar, INT_MAX);
    mp_image_params_set_dsize(out, dsize.num, dsize.den);

    if (p->spherical)
        out->spherical.type = p->spherical;
    for (int n = 0; n < 3; n++) {
        if (isfinite(p->spherical_ref_angles[n]))
            out->spherical.ref_angles[n] = p->spherical_ref_angles[n];
    }

    // Make sure the user-overrides are consistent (no RGB csp for YUV, etc.).
    mp_image_params_guess_csp(out);

    mp_pin_in_write(f->ppins[1], frame);
}