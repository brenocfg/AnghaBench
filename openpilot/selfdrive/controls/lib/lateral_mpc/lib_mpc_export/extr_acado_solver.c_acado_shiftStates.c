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
typedef  void* real_t ;
struct TYPE_4__ {void** x; void** od; void** u; } ;
struct TYPE_3__ {void** state; } ;

/* Variables and functions */
 TYPE_2__ acadoVariables ; 
 TYPE_1__ acadoWorkspace ; 
 int /*<<< orphan*/  acado_integrate (void**,int,int) ; 

void acado_shiftStates( int strategy, real_t* const xEnd, real_t* const uEnd )
{
int index;
for (index = 0; index < 20; ++index)
{
acadoVariables.x[index * 4] = acadoVariables.x[index * 4 + 4];
acadoVariables.x[index * 4 + 1] = acadoVariables.x[index * 4 + 5];
acadoVariables.x[index * 4 + 2] = acadoVariables.x[index * 4 + 6];
acadoVariables.x[index * 4 + 3] = acadoVariables.x[index * 4 + 7];
}

if (strategy == 1 && xEnd != 0)
{
acadoVariables.x[80] = xEnd[0];
acadoVariables.x[81] = xEnd[1];
acadoVariables.x[82] = xEnd[2];
acadoVariables.x[83] = xEnd[3];
}
else if (strategy == 2) 
{
acadoWorkspace.state[0] = acadoVariables.x[80];
acadoWorkspace.state[1] = acadoVariables.x[81];
acadoWorkspace.state[2] = acadoVariables.x[82];
acadoWorkspace.state[3] = acadoVariables.x[83];
if (uEnd != 0)
{
acadoWorkspace.state[24] = uEnd[0];
}
else
{
acadoWorkspace.state[24] = acadoVariables.u[19];
}
acadoWorkspace.state[25] = acadoVariables.od[340];
acadoWorkspace.state[26] = acadoVariables.od[341];
acadoWorkspace.state[27] = acadoVariables.od[342];
acadoWorkspace.state[28] = acadoVariables.od[343];
acadoWorkspace.state[29] = acadoVariables.od[344];
acadoWorkspace.state[30] = acadoVariables.od[345];
acadoWorkspace.state[31] = acadoVariables.od[346];
acadoWorkspace.state[32] = acadoVariables.od[347];
acadoWorkspace.state[33] = acadoVariables.od[348];
acadoWorkspace.state[34] = acadoVariables.od[349];
acadoWorkspace.state[35] = acadoVariables.od[350];
acadoWorkspace.state[36] = acadoVariables.od[351];
acadoWorkspace.state[37] = acadoVariables.od[352];
acadoWorkspace.state[38] = acadoVariables.od[353];
acadoWorkspace.state[39] = acadoVariables.od[354];
acadoWorkspace.state[40] = acadoVariables.od[355];
acadoWorkspace.state[41] = acadoVariables.od[356];

acado_integrate(acadoWorkspace.state, 1, 19);

acadoVariables.x[80] = acadoWorkspace.state[0];
acadoVariables.x[81] = acadoWorkspace.state[1];
acadoVariables.x[82] = acadoWorkspace.state[2];
acadoVariables.x[83] = acadoWorkspace.state[3];
}
}