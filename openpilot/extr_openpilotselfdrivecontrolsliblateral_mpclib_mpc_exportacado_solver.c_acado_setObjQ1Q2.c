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
tmpQ2[0] = + tmpFx[0]*tmpObjS[0] + tmpFx[4]*tmpObjS[5] + tmpFx[8]*tmpObjS[10] + tmpFx[12]*tmpObjS[15] + tmpFx[16]*tmpObjS[20];
tmpQ2[1] = + tmpFx[0]*tmpObjS[1] + tmpFx[4]*tmpObjS[6] + tmpFx[8]*tmpObjS[11] + tmpFx[12]*tmpObjS[16] + tmpFx[16]*tmpObjS[21];
tmpQ2[2] = + tmpFx[0]*tmpObjS[2] + tmpFx[4]*tmpObjS[7] + tmpFx[8]*tmpObjS[12] + tmpFx[12]*tmpObjS[17] + tmpFx[16]*tmpObjS[22];
tmpQ2[3] = + tmpFx[0]*tmpObjS[3] + tmpFx[4]*tmpObjS[8] + tmpFx[8]*tmpObjS[13] + tmpFx[12]*tmpObjS[18] + tmpFx[16]*tmpObjS[23];
tmpQ2[4] = + tmpFx[0]*tmpObjS[4] + tmpFx[4]*tmpObjS[9] + tmpFx[8]*tmpObjS[14] + tmpFx[12]*tmpObjS[19] + tmpFx[16]*tmpObjS[24];
tmpQ2[5] = + tmpFx[1]*tmpObjS[0] + tmpFx[5]*tmpObjS[5] + tmpFx[9]*tmpObjS[10] + tmpFx[13]*tmpObjS[15] + tmpFx[17]*tmpObjS[20];
tmpQ2[6] = + tmpFx[1]*tmpObjS[1] + tmpFx[5]*tmpObjS[6] + tmpFx[9]*tmpObjS[11] + tmpFx[13]*tmpObjS[16] + tmpFx[17]*tmpObjS[21];
tmpQ2[7] = + tmpFx[1]*tmpObjS[2] + tmpFx[5]*tmpObjS[7] + tmpFx[9]*tmpObjS[12] + tmpFx[13]*tmpObjS[17] + tmpFx[17]*tmpObjS[22];
tmpQ2[8] = + tmpFx[1]*tmpObjS[3] + tmpFx[5]*tmpObjS[8] + tmpFx[9]*tmpObjS[13] + tmpFx[13]*tmpObjS[18] + tmpFx[17]*tmpObjS[23];
tmpQ2[9] = + tmpFx[1]*tmpObjS[4] + tmpFx[5]*tmpObjS[9] + tmpFx[9]*tmpObjS[14] + tmpFx[13]*tmpObjS[19] + tmpFx[17]*tmpObjS[24];
tmpQ2[10] = + tmpFx[2]*tmpObjS[0] + tmpFx[6]*tmpObjS[5] + tmpFx[10]*tmpObjS[10] + tmpFx[14]*tmpObjS[15] + tmpFx[18]*tmpObjS[20];
tmpQ2[11] = + tmpFx[2]*tmpObjS[1] + tmpFx[6]*tmpObjS[6] + tmpFx[10]*tmpObjS[11] + tmpFx[14]*tmpObjS[16] + tmpFx[18]*tmpObjS[21];
tmpQ2[12] = + tmpFx[2]*tmpObjS[2] + tmpFx[6]*tmpObjS[7] + tmpFx[10]*tmpObjS[12] + tmpFx[14]*tmpObjS[17] + tmpFx[18]*tmpObjS[22];
tmpQ2[13] = + tmpFx[2]*tmpObjS[3] + tmpFx[6]*tmpObjS[8] + tmpFx[10]*tmpObjS[13] + tmpFx[14]*tmpObjS[18] + tmpFx[18]*tmpObjS[23];
tmpQ2[14] = + tmpFx[2]*tmpObjS[4] + tmpFx[6]*tmpObjS[9] + tmpFx[10]*tmpObjS[14] + tmpFx[14]*tmpObjS[19] + tmpFx[18]*tmpObjS[24];
tmpQ2[15] = + tmpFx[3]*tmpObjS[0] + tmpFx[7]*tmpObjS[5] + tmpFx[11]*tmpObjS[10] + tmpFx[15]*tmpObjS[15] + tmpFx[19]*tmpObjS[20];
tmpQ2[16] = + tmpFx[3]*tmpObjS[1] + tmpFx[7]*tmpObjS[6] + tmpFx[11]*tmpObjS[11] + tmpFx[15]*tmpObjS[16] + tmpFx[19]*tmpObjS[21];
tmpQ2[17] = + tmpFx[3]*tmpObjS[2] + tmpFx[7]*tmpObjS[7] + tmpFx[11]*tmpObjS[12] + tmpFx[15]*tmpObjS[17] + tmpFx[19]*tmpObjS[22];
tmpQ2[18] = + tmpFx[3]*tmpObjS[3] + tmpFx[7]*tmpObjS[8] + tmpFx[11]*tmpObjS[13] + tmpFx[15]*tmpObjS[18] + tmpFx[19]*tmpObjS[23];
tmpQ2[19] = + tmpFx[3]*tmpObjS[4] + tmpFx[7]*tmpObjS[9] + tmpFx[11]*tmpObjS[14] + tmpFx[15]*tmpObjS[19] + tmpFx[19]*tmpObjS[24];
tmpQ1[0] = + tmpQ2[0]*tmpFx[0] + tmpQ2[1]*tmpFx[4] + tmpQ2[2]*tmpFx[8] + tmpQ2[3]*tmpFx[12] + tmpQ2[4]*tmpFx[16];
tmpQ1[1] = + tmpQ2[0]*tmpFx[1] + tmpQ2[1]*tmpFx[5] + tmpQ2[2]*tmpFx[9] + tmpQ2[3]*tmpFx[13] + tmpQ2[4]*tmpFx[17];
tmpQ1[2] = + tmpQ2[0]*tmpFx[2] + tmpQ2[1]*tmpFx[6] + tmpQ2[2]*tmpFx[10] + tmpQ2[3]*tmpFx[14] + tmpQ2[4]*tmpFx[18];
tmpQ1[3] = + tmpQ2[0]*tmpFx[3] + tmpQ2[1]*tmpFx[7] + tmpQ2[2]*tmpFx[11] + tmpQ2[3]*tmpFx[15] + tmpQ2[4]*tmpFx[19];
tmpQ1[4] = + tmpQ2[5]*tmpFx[0] + tmpQ2[6]*tmpFx[4] + tmpQ2[7]*tmpFx[8] + tmpQ2[8]*tmpFx[12] + tmpQ2[9]*tmpFx[16];
tmpQ1[5] = + tmpQ2[5]*tmpFx[1] + tmpQ2[6]*tmpFx[5] + tmpQ2[7]*tmpFx[9] + tmpQ2[8]*tmpFx[13] + tmpQ2[9]*tmpFx[17];
tmpQ1[6] = + tmpQ2[5]*tmpFx[2] + tmpQ2[6]*tmpFx[6] + tmpQ2[7]*tmpFx[10] + tmpQ2[8]*tmpFx[14] + tmpQ2[9]*tmpFx[18];
tmpQ1[7] = + tmpQ2[5]*tmpFx[3] + tmpQ2[6]*tmpFx[7] + tmpQ2[7]*tmpFx[11] + tmpQ2[8]*tmpFx[15] + tmpQ2[9]*tmpFx[19];
tmpQ1[8] = + tmpQ2[10]*tmpFx[0] + tmpQ2[11]*tmpFx[4] + tmpQ2[12]*tmpFx[8] + tmpQ2[13]*tmpFx[12] + tmpQ2[14]*tmpFx[16];
tmpQ1[9] = + tmpQ2[10]*tmpFx[1] + tmpQ2[11]*tmpFx[5] + tmpQ2[12]*tmpFx[9] + tmpQ2[13]*tmpFx[13] + tmpQ2[14]*tmpFx[17];
tmpQ1[10] = + tmpQ2[10]*tmpFx[2] + tmpQ2[11]*tmpFx[6] + tmpQ2[12]*tmpFx[10] + tmpQ2[13]*tmpFx[14] + tmpQ2[14]*tmpFx[18];
tmpQ1[11] = + tmpQ2[10]*tmpFx[3] + tmpQ2[11]*tmpFx[7] + tmpQ2[12]*tmpFx[11] + tmpQ2[13]*tmpFx[15] + tmpQ2[14]*tmpFx[19];
tmpQ1[12] = + tmpQ2[15]*tmpFx[0] + tmpQ2[16]*tmpFx[4] + tmpQ2[17]*tmpFx[8] + tmpQ2[18]*tmpFx[12] + tmpQ2[19]*tmpFx[16];
tmpQ1[13] = + tmpQ2[15]*tmpFx[1] + tmpQ2[16]*tmpFx[5] + tmpQ2[17]*tmpFx[9] + tmpQ2[18]*tmpFx[13] + tmpQ2[19]*tmpFx[17];
tmpQ1[14] = + tmpQ2[15]*tmpFx[2] + tmpQ2[16]*tmpFx[6] + tmpQ2[17]*tmpFx[10] + tmpQ2[18]*tmpFx[14] + tmpQ2[19]*tmpFx[18];
tmpQ1[15] = + tmpQ2[15]*tmpFx[3] + tmpQ2[16]*tmpFx[7] + tmpQ2[17]*tmpFx[11] + tmpQ2[18]*tmpFx[15] + tmpQ2[19]*tmpFx[19];
}