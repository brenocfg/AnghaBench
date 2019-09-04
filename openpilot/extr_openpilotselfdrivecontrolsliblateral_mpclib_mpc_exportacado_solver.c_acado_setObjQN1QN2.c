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

void acado_setObjQN1QN2( real_t* const tmpFx, real_t* const tmpObjSEndTerm, real_t* const tmpQN1, real_t* const tmpQN2 )
{
tmpQN2[0] = + tmpFx[0]*tmpObjSEndTerm[0] + tmpFx[4]*tmpObjSEndTerm[4] + tmpFx[8]*tmpObjSEndTerm[8] + tmpFx[12]*tmpObjSEndTerm[12];
tmpQN2[1] = + tmpFx[0]*tmpObjSEndTerm[1] + tmpFx[4]*tmpObjSEndTerm[5] + tmpFx[8]*tmpObjSEndTerm[9] + tmpFx[12]*tmpObjSEndTerm[13];
tmpQN2[2] = + tmpFx[0]*tmpObjSEndTerm[2] + tmpFx[4]*tmpObjSEndTerm[6] + tmpFx[8]*tmpObjSEndTerm[10] + tmpFx[12]*tmpObjSEndTerm[14];
tmpQN2[3] = + tmpFx[0]*tmpObjSEndTerm[3] + tmpFx[4]*tmpObjSEndTerm[7] + tmpFx[8]*tmpObjSEndTerm[11] + tmpFx[12]*tmpObjSEndTerm[15];
tmpQN2[4] = + tmpFx[1]*tmpObjSEndTerm[0] + tmpFx[5]*tmpObjSEndTerm[4] + tmpFx[9]*tmpObjSEndTerm[8] + tmpFx[13]*tmpObjSEndTerm[12];
tmpQN2[5] = + tmpFx[1]*tmpObjSEndTerm[1] + tmpFx[5]*tmpObjSEndTerm[5] + tmpFx[9]*tmpObjSEndTerm[9] + tmpFx[13]*tmpObjSEndTerm[13];
tmpQN2[6] = + tmpFx[1]*tmpObjSEndTerm[2] + tmpFx[5]*tmpObjSEndTerm[6] + tmpFx[9]*tmpObjSEndTerm[10] + tmpFx[13]*tmpObjSEndTerm[14];
tmpQN2[7] = + tmpFx[1]*tmpObjSEndTerm[3] + tmpFx[5]*tmpObjSEndTerm[7] + tmpFx[9]*tmpObjSEndTerm[11] + tmpFx[13]*tmpObjSEndTerm[15];
tmpQN2[8] = + tmpFx[2]*tmpObjSEndTerm[0] + tmpFx[6]*tmpObjSEndTerm[4] + tmpFx[10]*tmpObjSEndTerm[8] + tmpFx[14]*tmpObjSEndTerm[12];
tmpQN2[9] = + tmpFx[2]*tmpObjSEndTerm[1] + tmpFx[6]*tmpObjSEndTerm[5] + tmpFx[10]*tmpObjSEndTerm[9] + tmpFx[14]*tmpObjSEndTerm[13];
tmpQN2[10] = + tmpFx[2]*tmpObjSEndTerm[2] + tmpFx[6]*tmpObjSEndTerm[6] + tmpFx[10]*tmpObjSEndTerm[10] + tmpFx[14]*tmpObjSEndTerm[14];
tmpQN2[11] = + tmpFx[2]*tmpObjSEndTerm[3] + tmpFx[6]*tmpObjSEndTerm[7] + tmpFx[10]*tmpObjSEndTerm[11] + tmpFx[14]*tmpObjSEndTerm[15];
tmpQN2[12] = + tmpFx[3]*tmpObjSEndTerm[0] + tmpFx[7]*tmpObjSEndTerm[4] + tmpFx[11]*tmpObjSEndTerm[8] + tmpFx[15]*tmpObjSEndTerm[12];
tmpQN2[13] = + tmpFx[3]*tmpObjSEndTerm[1] + tmpFx[7]*tmpObjSEndTerm[5] + tmpFx[11]*tmpObjSEndTerm[9] + tmpFx[15]*tmpObjSEndTerm[13];
tmpQN2[14] = + tmpFx[3]*tmpObjSEndTerm[2] + tmpFx[7]*tmpObjSEndTerm[6] + tmpFx[11]*tmpObjSEndTerm[10] + tmpFx[15]*tmpObjSEndTerm[14];
tmpQN2[15] = + tmpFx[3]*tmpObjSEndTerm[3] + tmpFx[7]*tmpObjSEndTerm[7] + tmpFx[11]*tmpObjSEndTerm[11] + tmpFx[15]*tmpObjSEndTerm[15];
tmpQN1[0] = + tmpQN2[0]*tmpFx[0] + tmpQN2[1]*tmpFx[4] + tmpQN2[2]*tmpFx[8] + tmpQN2[3]*tmpFx[12];
tmpQN1[1] = + tmpQN2[0]*tmpFx[1] + tmpQN2[1]*tmpFx[5] + tmpQN2[2]*tmpFx[9] + tmpQN2[3]*tmpFx[13];
tmpQN1[2] = + tmpQN2[0]*tmpFx[2] + tmpQN2[1]*tmpFx[6] + tmpQN2[2]*tmpFx[10] + tmpQN2[3]*tmpFx[14];
tmpQN1[3] = + tmpQN2[0]*tmpFx[3] + tmpQN2[1]*tmpFx[7] + tmpQN2[2]*tmpFx[11] + tmpQN2[3]*tmpFx[15];
tmpQN1[4] = + tmpQN2[4]*tmpFx[0] + tmpQN2[5]*tmpFx[4] + tmpQN2[6]*tmpFx[8] + tmpQN2[7]*tmpFx[12];
tmpQN1[5] = + tmpQN2[4]*tmpFx[1] + tmpQN2[5]*tmpFx[5] + tmpQN2[6]*tmpFx[9] + tmpQN2[7]*tmpFx[13];
tmpQN1[6] = + tmpQN2[4]*tmpFx[2] + tmpQN2[5]*tmpFx[6] + tmpQN2[6]*tmpFx[10] + tmpQN2[7]*tmpFx[14];
tmpQN1[7] = + tmpQN2[4]*tmpFx[3] + tmpQN2[5]*tmpFx[7] + tmpQN2[6]*tmpFx[11] + tmpQN2[7]*tmpFx[15];
tmpQN1[8] = + tmpQN2[8]*tmpFx[0] + tmpQN2[9]*tmpFx[4] + tmpQN2[10]*tmpFx[8] + tmpQN2[11]*tmpFx[12];
tmpQN1[9] = + tmpQN2[8]*tmpFx[1] + tmpQN2[9]*tmpFx[5] + tmpQN2[10]*tmpFx[9] + tmpQN2[11]*tmpFx[13];
tmpQN1[10] = + tmpQN2[8]*tmpFx[2] + tmpQN2[9]*tmpFx[6] + tmpQN2[10]*tmpFx[10] + tmpQN2[11]*tmpFx[14];
tmpQN1[11] = + tmpQN2[8]*tmpFx[3] + tmpQN2[9]*tmpFx[7] + tmpQN2[10]*tmpFx[11] + tmpQN2[11]*tmpFx[15];
tmpQN1[12] = + tmpQN2[12]*tmpFx[0] + tmpQN2[13]*tmpFx[4] + tmpQN2[14]*tmpFx[8] + tmpQN2[15]*tmpFx[12];
tmpQN1[13] = + tmpQN2[12]*tmpFx[1] + tmpQN2[13]*tmpFx[5] + tmpQN2[14]*tmpFx[9] + tmpQN2[15]*tmpFx[13];
tmpQN1[14] = + tmpQN2[12]*tmpFx[2] + tmpQN2[13]*tmpFx[6] + tmpQN2[14]*tmpFx[10] + tmpQN2[15]*tmpFx[14];
tmpQN1[15] = + tmpQN2[12]*tmpFx[3] + tmpQN2[13]*tmpFx[7] + tmpQN2[14]*tmpFx[11] + tmpQN2[15]*tmpFx[15];
}