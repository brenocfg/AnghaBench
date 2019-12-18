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
struct mp_csp_col_xy {scalar_t__ y; scalar_t__ x; } ;

/* Variables and functions */
 int fabs (scalar_t__) ; 
 int /*<<< orphan*/  mp_invert_matrix3x3 (float**) ; 
 int /*<<< orphan*/  mp_mul_matrix3x3 (float**,float**) ; 
 float mp_xy_X (struct mp_csp_col_xy) ; 
 float mp_xy_Z (struct mp_csp_col_xy) ; 

__attribute__((used)) static void mp_apply_chromatic_adaptation(struct mp_csp_col_xy src,
                                          struct mp_csp_col_xy dest, float m[3][3])
{
    // If the white points are nearly identical, this is a wasteful identity
    // operation.
    if (fabs(src.x - dest.x) < 1e-6 && fabs(src.y - dest.y) < 1e-6)
        return;

    // XYZd<-XYZs = Ma^-1 * (I*[Cd/Cs]) * Ma
    // http://www.brucelindbloom.com/index.html?Eqn_ChromAdapt.html
    float C[3][2], tmp[3][3] = {{0}};

    // Ma = Bradford matrix, arguably most popular method in use today.
    // This is derived experimentally and thus hard-coded.
    float bradford[3][3] = {
        {  0.8951,  0.2664, -0.1614 },
        { -0.7502,  1.7135,  0.0367 },
        {  0.0389, -0.0685,  1.0296 },
    };

    for (int i = 0; i < 3; i++) {
        // source cone
        C[i][0] = bradford[i][0] * mp_xy_X(src)
                + bradford[i][1] * 1
                + bradford[i][2] * mp_xy_Z(src);

        // dest cone
        C[i][1] = bradford[i][0] * mp_xy_X(dest)
                + bradford[i][1] * 1
                + bradford[i][2] * mp_xy_Z(dest);
    }

    // tmp := I * [Cd/Cs] * Ma
    for (int i = 0; i < 3; i++)
        tmp[i][i] = C[i][1] / C[i][0];

    mp_mul_matrix3x3(tmp, bradford);

    // M := M * Ma^-1 * tmp
    mp_invert_matrix3x3(bradford);
    mp_mul_matrix3x3(m, bradford);
    mp_mul_matrix3x3(m, tmp);
}