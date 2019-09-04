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
struct TYPE_4__ {int /*<<< orphan*/  WN; int /*<<< orphan*/ * od; int /*<<< orphan*/ * x; int /*<<< orphan*/ * W; int /*<<< orphan*/ * u; } ;
struct TYPE_3__ {int /*<<< orphan*/  QN2; int /*<<< orphan*/  QN1; int /*<<< orphan*/ * objValueOut; int /*<<< orphan*/ * DyN; int /*<<< orphan*/ * objValueIn; int /*<<< orphan*/ * R2; int /*<<< orphan*/ * R1; int /*<<< orphan*/ * Q2; int /*<<< orphan*/ * Q1; int /*<<< orphan*/ * Dy; } ;

/* Variables and functions */
 TYPE_2__ acadoVariables ; 
 TYPE_1__ acadoWorkspace ; 
 int /*<<< orphan*/  acado_evaluateLSQ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acado_evaluateLSQEndTerm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acado_setObjQ1Q2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acado_setObjQN1QN2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acado_setObjR1R2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void acado_evaluateObjective(  )
{
int runObj;
for (runObj = 0; runObj < 20; ++runObj)
{
acadoWorkspace.objValueIn[0] = acadoVariables.x[runObj * 4];
acadoWorkspace.objValueIn[1] = acadoVariables.x[runObj * 4 + 1];
acadoWorkspace.objValueIn[2] = acadoVariables.x[runObj * 4 + 2];
acadoWorkspace.objValueIn[3] = acadoVariables.x[runObj * 4 + 3];
acadoWorkspace.objValueIn[4] = acadoVariables.u[runObj];
acadoWorkspace.objValueIn[5] = acadoVariables.od[runObj * 18];
acadoWorkspace.objValueIn[6] = acadoVariables.od[runObj * 18 + 1];
acadoWorkspace.objValueIn[7] = acadoVariables.od[runObj * 18 + 2];
acadoWorkspace.objValueIn[8] = acadoVariables.od[runObj * 18 + 3];
acadoWorkspace.objValueIn[9] = acadoVariables.od[runObj * 18 + 4];
acadoWorkspace.objValueIn[10] = acadoVariables.od[runObj * 18 + 5];
acadoWorkspace.objValueIn[11] = acadoVariables.od[runObj * 18 + 6];
acadoWorkspace.objValueIn[12] = acadoVariables.od[runObj * 18 + 7];
acadoWorkspace.objValueIn[13] = acadoVariables.od[runObj * 18 + 8];
acadoWorkspace.objValueIn[14] = acadoVariables.od[runObj * 18 + 9];
acadoWorkspace.objValueIn[15] = acadoVariables.od[runObj * 18 + 10];
acadoWorkspace.objValueIn[16] = acadoVariables.od[runObj * 18 + 11];
acadoWorkspace.objValueIn[17] = acadoVariables.od[runObj * 18 + 12];
acadoWorkspace.objValueIn[18] = acadoVariables.od[runObj * 18 + 13];
acadoWorkspace.objValueIn[19] = acadoVariables.od[runObj * 18 + 14];
acadoWorkspace.objValueIn[20] = acadoVariables.od[runObj * 18 + 15];
acadoWorkspace.objValueIn[21] = acadoVariables.od[runObj * 18 + 16];
acadoWorkspace.objValueIn[22] = acadoVariables.od[runObj * 18 + 17];

acado_evaluateLSQ( acadoWorkspace.objValueIn, acadoWorkspace.objValueOut );
acadoWorkspace.Dy[runObj * 5] = acadoWorkspace.objValueOut[0];
acadoWorkspace.Dy[runObj * 5 + 1] = acadoWorkspace.objValueOut[1];
acadoWorkspace.Dy[runObj * 5 + 2] = acadoWorkspace.objValueOut[2];
acadoWorkspace.Dy[runObj * 5 + 3] = acadoWorkspace.objValueOut[3];
acadoWorkspace.Dy[runObj * 5 + 4] = acadoWorkspace.objValueOut[4];

acado_setObjQ1Q2( &(acadoWorkspace.objValueOut[ 5 ]), &(acadoVariables.W[ runObj * 25 ]), &(acadoWorkspace.Q1[ runObj * 16 ]), &(acadoWorkspace.Q2[ runObj * 20 ]) );

acado_setObjR1R2( &(acadoWorkspace.objValueOut[ 25 ]), &(acadoVariables.W[ runObj * 25 ]), &(acadoWorkspace.R1[ runObj ]), &(acadoWorkspace.R2[ runObj * 5 ]) );

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

acadoWorkspace.DyN[0] = acadoWorkspace.objValueOut[0];
acadoWorkspace.DyN[1] = acadoWorkspace.objValueOut[1];
acadoWorkspace.DyN[2] = acadoWorkspace.objValueOut[2];
acadoWorkspace.DyN[3] = acadoWorkspace.objValueOut[3];

acado_setObjQN1QN2( &(acadoWorkspace.objValueOut[ 4 ]), acadoVariables.WN, acadoWorkspace.QN1, acadoWorkspace.QN2 );

}