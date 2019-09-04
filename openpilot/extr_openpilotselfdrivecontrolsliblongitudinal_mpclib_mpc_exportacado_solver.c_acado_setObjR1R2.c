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

void acado_setObjR1R2( real_t* const tmpFu, real_t* const tmpObjS, real_t* const tmpR1, real_t* const tmpR2 )
{
tmpR2[0] = + tmpFu[0]*tmpObjS[0] + tmpFu[1]*tmpObjS[4] + tmpFu[2]*tmpObjS[8] + tmpFu[3]*tmpObjS[12];
tmpR2[1] = + tmpFu[0]*tmpObjS[1] + tmpFu[1]*tmpObjS[5] + tmpFu[2]*tmpObjS[9] + tmpFu[3]*tmpObjS[13];
tmpR2[2] = + tmpFu[0]*tmpObjS[2] + tmpFu[1]*tmpObjS[6] + tmpFu[2]*tmpObjS[10] + tmpFu[3]*tmpObjS[14];
tmpR2[3] = + tmpFu[0]*tmpObjS[3] + tmpFu[1]*tmpObjS[7] + tmpFu[2]*tmpObjS[11] + tmpFu[3]*tmpObjS[15];
tmpR1[0] = + tmpR2[0]*tmpFu[0] + tmpR2[1]*tmpFu[1] + tmpR2[2]*tmpFu[2] + tmpR2[3]*tmpFu[3];
}