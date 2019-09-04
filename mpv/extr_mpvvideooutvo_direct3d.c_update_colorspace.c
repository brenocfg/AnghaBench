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
struct mp_csp_params {int input_bits; int texture_bits; } ;
struct mp_cmat {int /*<<< orphan*/ * c; int /*<<< orphan*/ ** m; } ;
struct TYPE_6__ {int /*<<< orphan*/ ** m; } ;
struct TYPE_7__ {TYPE_2__ d3d_colormatrix; TYPE_1__* planes; scalar_t__ use_shaders; int /*<<< orphan*/  params; } ;
typedef  TYPE_3__ d3d_priv ;
struct TYPE_5__ {int bits_per_pixel; } ;

/* Variables and functions */
 struct mp_csp_params MP_CSP_PARAMS_DEFAULTS ; 
 int /*<<< orphan*/  mp_csp_set_image_params (struct mp_csp_params*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_get_csp_matrix (struct mp_csp_params*,struct mp_cmat*) ; 

__attribute__((used)) static void update_colorspace(d3d_priv *priv)
{
    struct mp_csp_params csp = MP_CSP_PARAMS_DEFAULTS;
    mp_csp_set_image_params(&csp, &priv->params);

    if (priv->use_shaders) {
        csp.input_bits = priv->planes[0].bits_per_pixel;
        csp.texture_bits = (csp.input_bits + 7) & ~7;

        struct mp_cmat coeff;
        mp_get_csp_matrix(&csp, &coeff);
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++)
                priv->d3d_colormatrix.m[row][col] = coeff.m[row][col];
            priv->d3d_colormatrix.m[row][3] = coeff.c[row];
        }
    }
}