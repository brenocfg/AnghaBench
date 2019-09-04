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
struct TYPE_4__ {scalar_t__* x; scalar_t__* od; scalar_t__* u; } ;
struct TYPE_3__ {scalar_t__* state; scalar_t__* evGu; scalar_t__* evGx; scalar_t__* d; } ;

/* Variables and functions */
 TYPE_2__ acadoVariables ; 
 TYPE_1__ acadoWorkspace ; 
 int acado_integrate (scalar_t__*,int,int) ; 

int acado_modelSimulation(  )
{
int ret;

int lRun1;
ret = 0;
for (lRun1 = 0; lRun1 < 20; ++lRun1)
{
acadoWorkspace.state[0] = acadoVariables.x[lRun1 * 4];
acadoWorkspace.state[1] = acadoVariables.x[lRun1 * 4 + 1];
acadoWorkspace.state[2] = acadoVariables.x[lRun1 * 4 + 2];
acadoWorkspace.state[3] = acadoVariables.x[lRun1 * 4 + 3];

acadoWorkspace.state[24] = acadoVariables.u[lRun1];
acadoWorkspace.state[25] = acadoVariables.od[lRun1 * 18];
acadoWorkspace.state[26] = acadoVariables.od[lRun1 * 18 + 1];
acadoWorkspace.state[27] = acadoVariables.od[lRun1 * 18 + 2];
acadoWorkspace.state[28] = acadoVariables.od[lRun1 * 18 + 3];
acadoWorkspace.state[29] = acadoVariables.od[lRun1 * 18 + 4];
acadoWorkspace.state[30] = acadoVariables.od[lRun1 * 18 + 5];
acadoWorkspace.state[31] = acadoVariables.od[lRun1 * 18 + 6];
acadoWorkspace.state[32] = acadoVariables.od[lRun1 * 18 + 7];
acadoWorkspace.state[33] = acadoVariables.od[lRun1 * 18 + 8];
acadoWorkspace.state[34] = acadoVariables.od[lRun1 * 18 + 9];
acadoWorkspace.state[35] = acadoVariables.od[lRun1 * 18 + 10];
acadoWorkspace.state[36] = acadoVariables.od[lRun1 * 18 + 11];
acadoWorkspace.state[37] = acadoVariables.od[lRun1 * 18 + 12];
acadoWorkspace.state[38] = acadoVariables.od[lRun1 * 18 + 13];
acadoWorkspace.state[39] = acadoVariables.od[lRun1 * 18 + 14];
acadoWorkspace.state[40] = acadoVariables.od[lRun1 * 18 + 15];
acadoWorkspace.state[41] = acadoVariables.od[lRun1 * 18 + 16];
acadoWorkspace.state[42] = acadoVariables.od[lRun1 * 18 + 17];

ret = acado_integrate(acadoWorkspace.state, 1, lRun1);

acadoWorkspace.d[lRun1 * 4] = acadoWorkspace.state[0] - acadoVariables.x[lRun1 * 4 + 4];
acadoWorkspace.d[lRun1 * 4 + 1] = acadoWorkspace.state[1] - acadoVariables.x[lRun1 * 4 + 5];
acadoWorkspace.d[lRun1 * 4 + 2] = acadoWorkspace.state[2] - acadoVariables.x[lRun1 * 4 + 6];
acadoWorkspace.d[lRun1 * 4 + 3] = acadoWorkspace.state[3] - acadoVariables.x[lRun1 * 4 + 7];

acadoWorkspace.evGx[lRun1 * 16] = acadoWorkspace.state[4];
acadoWorkspace.evGx[lRun1 * 16 + 1] = acadoWorkspace.state[5];
acadoWorkspace.evGx[lRun1 * 16 + 2] = acadoWorkspace.state[6];
acadoWorkspace.evGx[lRun1 * 16 + 3] = acadoWorkspace.state[7];
acadoWorkspace.evGx[lRun1 * 16 + 4] = acadoWorkspace.state[8];
acadoWorkspace.evGx[lRun1 * 16 + 5] = acadoWorkspace.state[9];
acadoWorkspace.evGx[lRun1 * 16 + 6] = acadoWorkspace.state[10];
acadoWorkspace.evGx[lRun1 * 16 + 7] = acadoWorkspace.state[11];
acadoWorkspace.evGx[lRun1 * 16 + 8] = acadoWorkspace.state[12];
acadoWorkspace.evGx[lRun1 * 16 + 9] = acadoWorkspace.state[13];
acadoWorkspace.evGx[lRun1 * 16 + 10] = acadoWorkspace.state[14];
acadoWorkspace.evGx[lRun1 * 16 + 11] = acadoWorkspace.state[15];
acadoWorkspace.evGx[lRun1 * 16 + 12] = acadoWorkspace.state[16];
acadoWorkspace.evGx[lRun1 * 16 + 13] = acadoWorkspace.state[17];
acadoWorkspace.evGx[lRun1 * 16 + 14] = acadoWorkspace.state[18];
acadoWorkspace.evGx[lRun1 * 16 + 15] = acadoWorkspace.state[19];

acadoWorkspace.evGu[lRun1 * 4] = acadoWorkspace.state[20];
acadoWorkspace.evGu[lRun1 * 4 + 1] = acadoWorkspace.state[21];
acadoWorkspace.evGu[lRun1 * 4 + 2] = acadoWorkspace.state[22];
acadoWorkspace.evGu[lRun1 * 4 + 3] = acadoWorkspace.state[23];
}
return ret;
}