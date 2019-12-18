#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mp_csp_primaries {int /*<<< orphan*/  white; } ;
typedef  enum mp_render_intent { ____Placeholder_mp_render_intent } mp_render_intent ;

/* Variables and functions */
 int MP_INTENT_ABSOLUTE_COLORIMETRIC ; 
 int MP_INTENT_SATURATION ; 
 int /*<<< orphan*/  mp_apply_chromatic_adaptation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float**) ; 
 int /*<<< orphan*/  mp_get_rgb2xyz_matrix (struct mp_csp_primaries,float**) ; 
 int /*<<< orphan*/  mp_invert_matrix3x3 (float**) ; 
 int /*<<< orphan*/  mp_mul_matrix3x3 (float**,float**) ; 

void mp_get_cms_matrix(struct mp_csp_primaries src, struct mp_csp_primaries dest,
                       enum mp_render_intent intent, float m[3][3])
{
    float tmp[3][3];

    // In saturation mapping, we don't care about accuracy and just want
    // primaries to map to primaries, making this an identity transformation.
    if (intent == MP_INTENT_SATURATION) {
        for (int i = 0; i < 3; i++)
            m[i][i] = 1;
        return;
    }

    // RGBd<-RGBs = RGBd<-XYZd * XYZd<-XYZs * XYZs<-RGBs
    // Equations from: http://www.brucelindbloom.com/index.html?Math.html
    // Note: Perceptual is treated like relative colorimetric. There's no
    // definition for perceptual other than "make it look good".

    // RGBd<-XYZd, inverted from XYZd<-RGBd
    mp_get_rgb2xyz_matrix(dest, m);
    mp_invert_matrix3x3(m);

    // Chromatic adaptation, except in absolute colorimetric intent
    if (intent != MP_INTENT_ABSOLUTE_COLORIMETRIC)
        mp_apply_chromatic_adaptation(src.white, dest.white, m);

    // XYZs<-RGBs
    mp_get_rgb2xyz_matrix(src, tmp);
    mp_mul_matrix3x3(m, tmp);
}