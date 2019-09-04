#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  double real_t ;
struct TYPE_4__ {double* y; double* yN; double* W; double* WN; int /*<<< orphan*/ * od; int /*<<< orphan*/ * x; int /*<<< orphan*/ * u; } ;
struct TYPE_3__ {double* objValueOut; double* Dy; double* DyN; int /*<<< orphan*/ * objValueIn; } ;

/* Variables and functions */
 TYPE_2__ acadoVariables ; 
 TYPE_1__ acadoWorkspace ; 
 int /*<<< orphan*/  acado_evaluateLSQ (int /*<<< orphan*/ *,double*) ; 
 int /*<<< orphan*/  acado_evaluateLSQEndTerm (int /*<<< orphan*/ *,double*) ; 

real_t acado_getObjective(  )
{
real_t objVal;

int lRun1;
/** Row vector of size: 5 */
real_t tmpDy[ 5 ];

/** Row vector of size: 4 */
real_t tmpDyN[ 4 ];

for (lRun1 = 0; lRun1 < 20; ++lRun1)
{
acadoWorkspace.objValueIn[0] = acadoVariables.x[lRun1 * 4];
acadoWorkspace.objValueIn[1] = acadoVariables.x[lRun1 * 4 + 1];
acadoWorkspace.objValueIn[2] = acadoVariables.x[lRun1 * 4 + 2];
acadoWorkspace.objValueIn[3] = acadoVariables.x[lRun1 * 4 + 3];
acadoWorkspace.objValueIn[4] = acadoVariables.u[lRun1];
acadoWorkspace.objValueIn[5] = acadoVariables.od[lRun1 * 18];
acadoWorkspace.objValueIn[6] = acadoVariables.od[lRun1 * 18 + 1];
acadoWorkspace.objValueIn[7] = acadoVariables.od[lRun1 * 18 + 2];
acadoWorkspace.objValueIn[8] = acadoVariables.od[lRun1 * 18 + 3];
acadoWorkspace.objValueIn[9] = acadoVariables.od[lRun1 * 18 + 4];
acadoWorkspace.objValueIn[10] = acadoVariables.od[lRun1 * 18 + 5];
acadoWorkspace.objValueIn[11] = acadoVariables.od[lRun1 * 18 + 6];
acadoWorkspace.objValueIn[12] = acadoVariables.od[lRun1 * 18 + 7];
acadoWorkspace.objValueIn[13] = acadoVariables.od[lRun1 * 18 + 8];
acadoWorkspace.objValueIn[14] = acadoVariables.od[lRun1 * 18 + 9];
acadoWorkspace.objValueIn[15] = acadoVariables.od[lRun1 * 18 + 10];
acadoWorkspace.objValueIn[16] = acadoVariables.od[lRun1 * 18 + 11];
acadoWorkspace.objValueIn[17] = acadoVariables.od[lRun1 * 18 + 12];
acadoWorkspace.objValueIn[18] = acadoVariables.od[lRun1 * 18 + 13];
acadoWorkspace.objValueIn[19] = acadoVariables.od[lRun1 * 18 + 14];
acadoWorkspace.objValueIn[20] = acadoVariables.od[lRun1 * 18 + 15];
acadoWorkspace.objValueIn[21] = acadoVariables.od[lRun1 * 18 + 16];
acadoWorkspace.objValueIn[22] = acadoVariables.od[lRun1 * 18 + 17];

acado_evaluateLSQ( acadoWorkspace.objValueIn, acadoWorkspace.objValueOut );
acadoWorkspace.Dy[lRun1 * 5] = acadoWorkspace.objValueOut[0] - acadoVariables.y[lRun1 * 5];
acadoWorkspace.Dy[lRun1 * 5 + 1] = acadoWorkspace.objValueOut[1] - acadoVariables.y[lRun1 * 5 + 1];
acadoWorkspace.Dy[lRun1 * 5 + 2] = acadoWorkspace.objValueOut[2] - acadoVariables.y[lRun1 * 5 + 2];
acadoWorkspace.Dy[lRun1 * 5 + 3] = acadoWorkspace.objValueOut[3] - acadoVariables.y[lRun1 * 5 + 3];
acadoWorkspace.Dy[lRun1 * 5 + 4] = acadoWorkspace.objValueOut[4] - acadoVariables.y[lRun1 * 5 + 4];
}
acadoWorkspace.objValueIn[0] = acadoVariables.x[80];
acadoWorkspace.objValueIn[1] = acadoVariables.x[81];
acadoWorkspace.objValueIn[2] = acadoVariables.x[82];
acadoWorkspace.objValueIn[3] = acadoVariables.x[83];
acadoWorkspace.objValueIn[4] = acadoVariables.od[360];
acadoWorkspace.objValueIn[5] = acadoVariables.od[361];
acadoWorkspace.objValueIn[6] = acadoVariables.od[362];
acadoWorkspace.objValueIn[7] = acadoVariables.od[363];
acadoWorkspace.objValueIn[8] = acadoVariables.od[364];
acadoWorkspace.objValueIn[9] = acadoVariables.od[365];
acadoWorkspace.objValueIn[10] = acadoVariables.od[366];
acadoWorkspace.objValueIn[11] = acadoVariables.od[367];
acadoWorkspace.objValueIn[12] = acadoVariables.od[368];
acadoWorkspace.objValueIn[13] = acadoVariables.od[369];
acadoWorkspace.objValueIn[14] = acadoVariables.od[370];
acadoWorkspace.objValueIn[15] = acadoVariables.od[371];
acadoWorkspace.objValueIn[16] = acadoVariables.od[372];
acadoWorkspace.objValueIn[17] = acadoVariables.od[373];
acadoWorkspace.objValueIn[18] = acadoVariables.od[374];
acadoWorkspace.objValueIn[19] = acadoVariables.od[375];
acadoWorkspace.objValueIn[20] = acadoVariables.od[376];
acadoWorkspace.objValueIn[21] = acadoVariables.od[377];
acado_evaluateLSQEndTerm( acadoWorkspace.objValueIn, acadoWorkspace.objValueOut );
acadoWorkspace.DyN[0] = acadoWorkspace.objValueOut[0] - acadoVariables.yN[0];
acadoWorkspace.DyN[1] = acadoWorkspace.objValueOut[1] - acadoVariables.yN[1];
acadoWorkspace.DyN[2] = acadoWorkspace.objValueOut[2] - acadoVariables.yN[2];
acadoWorkspace.DyN[3] = acadoWorkspace.objValueOut[3] - acadoVariables.yN[3];
objVal = 0.0000000000000000e+00;
for (lRun1 = 0; lRun1 < 20; ++lRun1)
{
tmpDy[0] = + acadoWorkspace.Dy[lRun1 * 5]*acadoVariables.W[lRun1 * 25] + acadoWorkspace.Dy[lRun1 * 5 + 1]*acadoVariables.W[lRun1 * 25 + 5] + acadoWorkspace.Dy[lRun1 * 5 + 2]*acadoVariables.W[lRun1 * 25 + 10] + acadoWorkspace.Dy[lRun1 * 5 + 3]*acadoVariables.W[lRun1 * 25 + 15] + acadoWorkspace.Dy[lRun1 * 5 + 4]*acadoVariables.W[lRun1 * 25 + 20];
tmpDy[1] = + acadoWorkspace.Dy[lRun1 * 5]*acadoVariables.W[lRun1 * 25 + 1] + acadoWorkspace.Dy[lRun1 * 5 + 1]*acadoVariables.W[lRun1 * 25 + 6] + acadoWorkspace.Dy[lRun1 * 5 + 2]*acadoVariables.W[lRun1 * 25 + 11] + acadoWorkspace.Dy[lRun1 * 5 + 3]*acadoVariables.W[lRun1 * 25 + 16] + acadoWorkspace.Dy[lRun1 * 5 + 4]*acadoVariables.W[lRun1 * 25 + 21];
tmpDy[2] = + acadoWorkspace.Dy[lRun1 * 5]*acadoVariables.W[lRun1 * 25 + 2] + acadoWorkspace.Dy[lRun1 * 5 + 1]*acadoVariables.W[lRun1 * 25 + 7] + acadoWorkspace.Dy[lRun1 * 5 + 2]*acadoVariables.W[lRun1 * 25 + 12] + acadoWorkspace.Dy[lRun1 * 5 + 3]*acadoVariables.W[lRun1 * 25 + 17] + acadoWorkspace.Dy[lRun1 * 5 + 4]*acadoVariables.W[lRun1 * 25 + 22];
tmpDy[3] = + acadoWorkspace.Dy[lRun1 * 5]*acadoVariables.W[lRun1 * 25 + 3] + acadoWorkspace.Dy[lRun1 * 5 + 1]*acadoVariables.W[lRun1 * 25 + 8] + acadoWorkspace.Dy[lRun1 * 5 + 2]*acadoVariables.W[lRun1 * 25 + 13] + acadoWorkspace.Dy[lRun1 * 5 + 3]*acadoVariables.W[lRun1 * 25 + 18] + acadoWorkspace.Dy[lRun1 * 5 + 4]*acadoVariables.W[lRun1 * 25 + 23];
tmpDy[4] = + acadoWorkspace.Dy[lRun1 * 5]*acadoVariables.W[lRun1 * 25 + 4] + acadoWorkspace.Dy[lRun1 * 5 + 1]*acadoVariables.W[lRun1 * 25 + 9] + acadoWorkspace.Dy[lRun1 * 5 + 2]*acadoVariables.W[lRun1 * 25 + 14] + acadoWorkspace.Dy[lRun1 * 5 + 3]*acadoVariables.W[lRun1 * 25 + 19] + acadoWorkspace.Dy[lRun1 * 5 + 4]*acadoVariables.W[lRun1 * 25 + 24];
objVal += + acadoWorkspace.Dy[lRun1 * 5]*tmpDy[0] + acadoWorkspace.Dy[lRun1 * 5 + 1]*tmpDy[1] + acadoWorkspace.Dy[lRun1 * 5 + 2]*tmpDy[2] + acadoWorkspace.Dy[lRun1 * 5 + 3]*tmpDy[3] + acadoWorkspace.Dy[lRun1 * 5 + 4]*tmpDy[4];
}

tmpDyN[0] = + acadoWorkspace.DyN[0]*acadoVariables.WN[0] + acadoWorkspace.DyN[1]*acadoVariables.WN[4] + acadoWorkspace.DyN[2]*acadoVariables.WN[8] + acadoWorkspace.DyN[3]*acadoVariables.WN[12];
tmpDyN[1] = + acadoWorkspace.DyN[0]*acadoVariables.WN[1] + acadoWorkspace.DyN[1]*acadoVariables.WN[5] + acadoWorkspace.DyN[2]*acadoVariables.WN[9] + acadoWorkspace.DyN[3]*acadoVariables.WN[13];
tmpDyN[2] = + acadoWorkspace.DyN[0]*acadoVariables.WN[2] + acadoWorkspace.DyN[1]*acadoVariables.WN[6] + acadoWorkspace.DyN[2]*acadoVariables.WN[10] + acadoWorkspace.DyN[3]*acadoVariables.WN[14];
tmpDyN[3] = + acadoWorkspace.DyN[0]*acadoVariables.WN[3] + acadoWorkspace.DyN[1]*acadoVariables.WN[7] + acadoWorkspace.DyN[2]*acadoVariables.WN[11] + acadoWorkspace.DyN[3]*acadoVariables.WN[15];
objVal += + acadoWorkspace.DyN[0]*tmpDyN[0] + acadoWorkspace.DyN[1]*tmpDyN[1] + acadoWorkspace.DyN[2]*tmpDyN[2] + acadoWorkspace.DyN[3]*tmpDyN[3];

objVal *= 0.5;
return objVal;
}