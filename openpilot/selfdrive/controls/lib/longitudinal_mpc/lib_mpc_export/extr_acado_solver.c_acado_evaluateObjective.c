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
acadoWorkspace.objValueIn[0] = acadoVariables.x[runObj * 3];
acadoWorkspace.objValueIn[1] = acadoVariables.x[runObj * 3 + 1];
acadoWorkspace.objValueIn[2] = acadoVariables.x[runObj * 3 + 2];
acadoWorkspace.objValueIn[3] = acadoVariables.u[runObj];
acadoWorkspace.objValueIn[4] = acadoVariables.od[runObj * 2];
acadoWorkspace.objValueIn[5] = acadoVariables.od[runObj * 2 + 1];

acado_evaluateLSQ( acadoWorkspace.objValueIn, acadoWorkspace.objValueOut );
acadoWorkspace.Dy[runObj * 4] = acadoWorkspace.objValueOut[0];
acadoWorkspace.Dy[runObj * 4 + 1] = acadoWorkspace.objValueOut[1];
acadoWorkspace.Dy[runObj * 4 + 2] = acadoWorkspace.objValueOut[2];
acadoWorkspace.Dy[runObj * 4 + 3] = acadoWorkspace.objValueOut[3];

acado_setObjQ1Q2( &(acadoWorkspace.objValueOut[ 4 ]), &(acadoVariables.W[ runObj * 16 ]), &(acadoWorkspace.Q1[ runObj * 9 ]), &(acadoWorkspace.Q2[ runObj * 12 ]) );

acado_setObjR1R2( &(acadoWorkspace.objValueOut[ 16 ]), &(acadoVariables.W[ runObj * 16 ]), &(acadoWorkspace.R1[ runObj ]), &(acadoWorkspace.R2[ runObj * 4 ]) );

}
acadoWorkspace.objValueIn[0] = acadoVariables.x[60];
acadoWorkspace.objValueIn[1] = acadoVariables.x[61];
acadoWorkspace.objValueIn[2] = acadoVariables.x[62];
acadoWorkspace.objValueIn[3] = acadoVariables.od[40];
acadoWorkspace.objValueIn[4] = acadoVariables.od[41];
acado_evaluateLSQEndTerm( acadoWorkspace.objValueIn, acadoWorkspace.objValueOut );

acadoWorkspace.DyN[0] = acadoWorkspace.objValueOut[0];
acadoWorkspace.DyN[1] = acadoWorkspace.objValueOut[1];
acadoWorkspace.DyN[2] = acadoWorkspace.objValueOut[2];

acado_setObjQN1QN2( &(acadoWorkspace.objValueOut[ 3 ]), acadoVariables.WN, acadoWorkspace.QN1, acadoWorkspace.QN2 );

}