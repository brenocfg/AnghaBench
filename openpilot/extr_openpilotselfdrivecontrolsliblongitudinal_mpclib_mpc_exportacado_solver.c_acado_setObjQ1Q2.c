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
typedef  int real_t ;

/* Variables and functions */

void acado_setObjQ1Q2( real_t* const tmpFx, real_t* const tmpObjS, real_t* const tmpQ1, real_t* const tmpQ2 )
{
tmpQ2[0] = + tmpFx[0]*tmpObjS[0] + tmpFx[3]*tmpObjS[4] + tmpFx[6]*tmpObjS[8] + tmpFx[9]*tmpObjS[12];
tmpQ2[1] = + tmpFx[0]*tmpObjS[1] + tmpFx[3]*tmpObjS[5] + tmpFx[6]*tmpObjS[9] + tmpFx[9]*tmpObjS[13];
tmpQ2[2] = + tmpFx[0]*tmpObjS[2] + tmpFx[3]*tmpObjS[6] + tmpFx[6]*tmpObjS[10] + tmpFx[9]*tmpObjS[14];
tmpQ2[3] = + tmpFx[0]*tmpObjS[3] + tmpFx[3]*tmpObjS[7] + tmpFx[6]*tmpObjS[11] + tmpFx[9]*tmpObjS[15];
tmpQ2[4] = + tmpFx[1]*tmpObjS[0] + tmpFx[4]*tmpObjS[4] + tmpFx[7]*tmpObjS[8] + tmpFx[10]*tmpObjS[12];
tmpQ2[5] = + tmpFx[1]*tmpObjS[1] + tmpFx[4]*tmpObjS[5] + tmpFx[7]*tmpObjS[9] + tmpFx[10]*tmpObjS[13];
tmpQ2[6] = + tmpFx[1]*tmpObjS[2] + tmpFx[4]*tmpObjS[6] + tmpFx[7]*tmpObjS[10] + tmpFx[10]*tmpObjS[14];
tmpQ2[7] = + tmpFx[1]*tmpObjS[3] + tmpFx[4]*tmpObjS[7] + tmpFx[7]*tmpObjS[11] + tmpFx[10]*tmpObjS[15];
tmpQ2[8] = + tmpFx[2]*tmpObjS[0] + tmpFx[5]*tmpObjS[4] + tmpFx[8]*tmpObjS[8] + tmpFx[11]*tmpObjS[12];
tmpQ2[9] = + tmpFx[2]*tmpObjS[1] + tmpFx[5]*tmpObjS[5] + tmpFx[8]*tmpObjS[9] + tmpFx[11]*tmpObjS[13];
tmpQ2[10] = + tmpFx[2]*tmpObjS[2] + tmpFx[5]*tmpObjS[6] + tmpFx[8]*tmpObjS[10] + tmpFx[11]*tmpObjS[14];
tmpQ2[11] = + tmpFx[2]*tmpObjS[3] + tmpFx[5]*tmpObjS[7] + tmpFx[8]*tmpObjS[11] + tmpFx[11]*tmpObjS[15];
tmpQ1[0] = + tmpQ2[0]*tmpFx[0] + tmpQ2[1]*tmpFx[3] + tmpQ2[2]*tmpFx[6] + tmpQ2[3]*tmpFx[9];
tmpQ1[1] = + tmpQ2[0]*tmpFx[1] + tmpQ2[1]*tmpFx[4] + tmpQ2[2]*tmpFx[7] + tmpQ2[3]*tmpFx[10];
tmpQ1[2] = + tmpQ2[0]*tmpFx[2] + tmpQ2[1]*tmpFx[5] + tmpQ2[2]*tmpFx[8] + tmpQ2[3]*tmpFx[11];
tmpQ1[3] = + tmpQ2[4]*tmpFx[0] + tmpQ2[5]*tmpFx[3] + tmpQ2[6]*tmpFx[6] + tmpQ2[7]*tmpFx[9];
tmpQ1[4] = + tmpQ2[4]*tmpFx[1] + tmpQ2[5]*tmpFx[4] + tmpQ2[6]*tmpFx[7] + tmpQ2[7]*tmpFx[10];
tmpQ1[5] = + tmpQ2[4]*tmpFx[2] + tmpQ2[5]*tmpFx[5] + tmpQ2[6]*tmpFx[8] + tmpQ2[7]*tmpFx[11];
tmpQ1[6] = + tmpQ2[8]*tmpFx[0] + tmpQ2[9]*tmpFx[3] + tmpQ2[10]*tmpFx[6] + tmpQ2[11]*tmpFx[9];
tmpQ1[7] = + tmpQ2[8]*tmpFx[1] + tmpQ2[9]*tmpFx[4] + tmpQ2[10]*tmpFx[7] + tmpQ2[11]*tmpFx[10];
tmpQ1[8] = + tmpQ2[8]*tmpFx[2] + tmpQ2[9]*tmpFx[5] + tmpQ2[10]*tmpFx[8] + tmpQ2[11]*tmpFx[11];
}