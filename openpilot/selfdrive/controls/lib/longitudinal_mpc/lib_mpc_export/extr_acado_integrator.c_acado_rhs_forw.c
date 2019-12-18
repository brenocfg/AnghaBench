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
typedef  int /*<<< orphan*/  real_t ;

/* Variables and functions */

void acado_rhs_forw(const real_t* in, real_t* out)
{
const real_t* xd = in;
const real_t* u = in + 15;

/* Compute outputs: */
out[0] = xd[1];
out[1] = xd[2];
out[2] = u[0];
out[3] = xd[6];
out[4] = xd[7];
out[5] = xd[8];
out[6] = xd[9];
out[7] = xd[10];
out[8] = xd[11];
out[9] = (real_t)(0.0000000000000000e+00);
out[10] = (real_t)(0.0000000000000000e+00);
out[11] = (real_t)(0.0000000000000000e+00);
out[12] = xd[13];
out[13] = xd[14];
out[14] = (real_t)(1.0000000000000000e+00);
}