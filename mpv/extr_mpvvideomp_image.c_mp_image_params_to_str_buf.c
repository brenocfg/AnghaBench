#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; float* ref_angles; } ;
struct TYPE_3__ {scalar_t__ space; scalar_t__ primaries; scalar_t__ gamma; scalar_t__ levels; scalar_t__ light; scalar_t__ sig_peak; } ;
struct mp_image_params {int w; int h; scalar_t__ p_w; scalar_t__ p_h; scalar_t__ chroma_location; scalar_t__ stereo3d; TYPE_2__ spherical; scalar_t__ rotate; TYPE_1__ color; scalar_t__ hw_flags; scalar_t__ hw_subfmt; scalar_t__ imgfmt; } ;

/* Variables and functions */
 scalar_t__ MP_SPHERICAL_NONE ; 
 int /*<<< orphan*/  MP_STEREO3D_NAME_DEF (scalar_t__,char*) ; 
 int /*<<< orphan*/  m_opt_choice_str (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mp_chroma_names ; 
 int /*<<< orphan*/  mp_csp_levels_names ; 
 int /*<<< orphan*/  mp_csp_light_names ; 
 int /*<<< orphan*/  mp_csp_names ; 
 int /*<<< orphan*/  mp_csp_prim_names ; 
 int /*<<< orphan*/  mp_csp_trc_names ; 
 int /*<<< orphan*/  mp_imgfmt_to_name (scalar_t__) ; 
 int /*<<< orphan*/  mp_snprintf_cat (char*,size_t,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  mp_spherical_names ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 

char *mp_image_params_to_str_buf(char *b, size_t bs,
                                 const struct mp_image_params *p)
{
    if (p && p->imgfmt) {
        snprintf(b, bs, "%dx%d", p->w, p->h);
        if (p->p_w != p->p_h || !p->p_w)
            mp_snprintf_cat(b, bs, " [%d:%d]", p->p_w, p->p_h);
        mp_snprintf_cat(b, bs, " %s", mp_imgfmt_to_name(p->imgfmt));
        if (p->hw_subfmt)
            mp_snprintf_cat(b, bs, "[%s]", mp_imgfmt_to_name(p->hw_subfmt));
        if (p->hw_flags)
            mp_snprintf_cat(b, bs, "[0x%x]", p->hw_flags);
        mp_snprintf_cat(b, bs, " %s/%s/%s/%s/%s",
                        m_opt_choice_str(mp_csp_names, p->color.space),
                        m_opt_choice_str(mp_csp_prim_names, p->color.primaries),
                        m_opt_choice_str(mp_csp_trc_names, p->color.gamma),
                        m_opt_choice_str(mp_csp_levels_names, p->color.levels),
                        m_opt_choice_str(mp_csp_light_names, p->color.light));
        if (p->color.sig_peak)
            mp_snprintf_cat(b, bs, " SP=%f", p->color.sig_peak);
        mp_snprintf_cat(b, bs, " CL=%s",
                        m_opt_choice_str(mp_chroma_names, p->chroma_location));
        if (p->rotate)
            mp_snprintf_cat(b, bs, " rot=%d", p->rotate);
        if (p->stereo3d > 0) {
            mp_snprintf_cat(b, bs, " stereo=%s",
                            MP_STEREO3D_NAME_DEF(p->stereo3d, "?"));
        }
        if (p->spherical.type != MP_SPHERICAL_NONE) {
            const float *a = p->spherical.ref_angles;
            mp_snprintf_cat(b, bs, " (%s %f/%f/%f)",
                            m_opt_choice_str(mp_spherical_names, p->spherical.type),
                            a[0], a[1], a[2]);
        }
    } else {
        snprintf(b, bs, "???");
    }
    return b;
}