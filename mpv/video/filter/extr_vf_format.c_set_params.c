#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vf_format_opts {int gamma; double sig_peak; scalar_t__ rotate; scalar_t__ dw; scalar_t__ dh; scalar_t__ dar; scalar_t__ stereo_in; scalar_t__ chroma_location; scalar_t__ light; scalar_t__ primaries; scalar_t__ colorlevels; scalar_t__ colormatrix; } ;
struct TYPE_4__ {int gamma; double sig_peak; scalar_t__ light; scalar_t__ primaries; scalar_t__ levels; scalar_t__ space; } ;
struct mp_image_params {scalar_t__ rotate; scalar_t__ stereo3d; scalar_t__ chroma_location; TYPE_1__ color; } ;
typedef  enum mp_csp_trc { ____Placeholder_mp_csp_trc } mp_csp_trc ;
struct TYPE_5__ {scalar_t__ num; scalar_t__ den; } ;
typedef  TYPE_2__ AVRational ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ MP_CSP_LIGHT_AUTO ; 
 TYPE_2__ av_d2q (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_params_get_dsize (struct mp_image_params*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  mp_image_params_set_dsize (struct mp_image_params*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void set_params(struct vf_format_opts *p, struct mp_image_params *out)
{
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
}