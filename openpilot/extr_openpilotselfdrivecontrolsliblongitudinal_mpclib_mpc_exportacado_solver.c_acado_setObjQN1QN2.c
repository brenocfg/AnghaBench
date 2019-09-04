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
tmpQN2[0] = + tmpFx[0]*tmpObjSEndTerm[0] + tmpFx[3]*tmpObjSEndTerm[3] + tmpFx[6]*tmpObjSEndTerm[6];
tmpQN2[1] = + tmpFx[0]*tmpObjSEndTerm[1] + tmpFx[3]*tmpObjSEndTerm[4] + tmpFx[6]*tmpObjSEndTerm[7];
tmpQN2[2] = + tmpFx[0]*tmpObjSEndTerm[2] + tmpFx[3]*tmpObjSEndTerm[5] + tmpFx[6]*tmpObjSEndTerm[8];
tmpQN2[3] = + tmpFx[1]*tmpObjSEndTerm[0] + tmpFx[4]*tmpObjSEndTerm[3] + tmpFx[7]*tmpObjSEndTerm[6];
tmpQN2[4] = + tmpFx[1]*tmpObjSEndTerm[1] + tmpFx[4]*tmpObjSEndTerm[4] + tmpFx[7]*tmpObjSEndTerm[7];
tmpQN2[5] = + tmpFx[1]*tmpObjSEndTerm[2] + tmpFx[4]*tmpObjSEndTerm[5] + tmpFx[7]*tmpObjSEndTerm[8];
tmpQN2[6] = + tmpFx[2]*tmpObjSEndTerm[0] + tmpFx[5]*tmpObjSEndTerm[3] + tmpFx[8]*tmpObjSEndTerm[6];
tmpQN2[7] = + tmpFx[2]*tmpObjSEndTerm[1] + tmpFx[5]*tmpObjSEndTerm[4] + tmpFx[8]*tmpObjSEndTerm[7];
tmpQN2[8] = + tmpFx[2]*tmpObjSEndTerm[2] + tmpFx[5]*tmpObjSEndTerm[5] + tmpFx[8]*tmpObjSEndTerm[8];
tmpQN1[0] = + tmpQN2[0]*tmpFx[0] + tmpQN2[1]*tmpFx[3] + tmpQN2[2]*tmpFx[6];
tmpQN1[1] = + tmpQN2[0]*tmpFx[1] + tmpQN2[1]*tmpFx[4] + tmpQN2[2]*tmpFx[7];
tmpQN1[2] = + tmpQN2[0]*tmpFx[2] + tmpQN2[1]*tmpFx[5] + tmpQN2[2]*tmpFx[8];
tmpQN1[3] = + tmpQN2[3]*tmpFx[0] + tmpQN2[4]*tmpFx[3] + tmpQN2[5]*tmpFx[6];
tmpQN1[4] = + tmpQN2[3]*tmpFx[1] + tmpQN2[4]*tmpFx[4] + tmpQN2[5]*tmpFx[7];
tmpQN1[5] = + tmpQN2[3]*tmpFx[2] + tmpQN2[4]*tmpFx[5] + tmpQN2[5]*tmpFx[8];
tmpQN1[6] = + tmpQN2[6]*tmpFx[0] + tmpQN2[7]*tmpFx[3] + tmpQN2[8]*tmpFx[6];
tmpQN1[7] = + tmpQN2[6]*tmpFx[1] + tmpQN2[7]*tmpFx[4] + tmpQN2[8]*tmpFx[7];
tmpQN1[8] = + tmpQN2[6]*tmpFx[2] + tmpQN2[7]*tmpFx[5] + tmpQN2[8]*tmpFx[8];
}