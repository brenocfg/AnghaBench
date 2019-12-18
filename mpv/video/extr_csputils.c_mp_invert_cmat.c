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
struct mp_cmat {int** m; int* c; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_invert_matrix3x3 (int**) ; 

void mp_invert_cmat(struct mp_cmat *out, struct mp_cmat *in)
{
    *out = *in;
    mp_invert_matrix3x3(out->m);

    // fix the constant coefficient
    // rgb = M * yuv + C
    // M^-1 * rgb = yuv + M^-1 * C
    // yuv = M^-1 * rgb - M^-1 * C
    //                  ^^^^^^^^^^
    out->c[0] = -(out->m[0][0] * in->c[0] + out->m[0][1] * in->c[1] + out->m[0][2] * in->c[2]);
    out->c[1] = -(out->m[1][0] * in->c[0] + out->m[1][1] * in->c[1] + out->m[1][2] * in->c[2]);
    out->c[2] = -(out->m[2][0] * in->c[0] + out->m[2][1] * in->c[1] + out->m[2][2] * in->c[2]);
}