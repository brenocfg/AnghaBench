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
struct TYPE_4__ {int /*<<< orphan*/ * x; int /*<<< orphan*/ * od; int /*<<< orphan*/ * u; } ;
struct TYPE_3__ {int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 TYPE_2__ acadoVariables ; 
 TYPE_1__ acadoWorkspace ; 
 int /*<<< orphan*/  acado_integrate (int /*<<< orphan*/ *,int,int) ; 

void acado_initializeNodesByForwardSimulation(  )
{
int index;
for (index = 0; index < 20; ++index)
{
acadoWorkspace.state[0] = acadoVariables.x[index * 4];
acadoWorkspace.state[1] = acadoVariables.x[index * 4 + 1];
acadoWorkspace.state[2] = acadoVariables.x[index * 4 + 2];
acadoWorkspace.state[3] = acadoVariables.x[index * 4 + 3];
acadoWorkspace.state[24] = acadoVariables.u[index];
acadoWorkspace.state[25] = acadoVariables.od[index * 17];
acadoWorkspace.state[26] = acadoVariables.od[index * 17 + 1];
acadoWorkspace.state[27] = acadoVariables.od[index * 17 + 2];
acadoWorkspace.state[28] = acadoVariables.od[index * 17 + 3];
acadoWorkspace.state[29] = acadoVariables.od[index * 17 + 4];
acadoWorkspace.state[30] = acadoVariables.od[index * 17 + 5];
acadoWorkspace.state[31] = acadoVariables.od[index * 17 + 6];
acadoWorkspace.state[32] = acadoVariables.od[index * 17 + 7];
acadoWorkspace.state[33] = acadoVariables.od[index * 17 + 8];
acadoWorkspace.state[34] = acadoVariables.od[index * 17 + 9];
acadoWorkspace.state[35] = acadoVariables.od[index * 17 + 10];
acadoWorkspace.state[36] = acadoVariables.od[index * 17 + 11];
acadoWorkspace.state[37] = acadoVariables.od[index * 17 + 12];
acadoWorkspace.state[38] = acadoVariables.od[index * 17 + 13];
acadoWorkspace.state[39] = acadoVariables.od[index * 17 + 14];
acadoWorkspace.state[40] = acadoVariables.od[index * 17 + 15];
acadoWorkspace.state[41] = acadoVariables.od[index * 17 + 16];

acado_integrate(acadoWorkspace.state, index == 0, index);

acadoVariables.x[index * 4 + 4] = acadoWorkspace.state[0];
acadoVariables.x[index * 4 + 5] = acadoWorkspace.state[1];
acadoVariables.x[index * 4 + 6] = acadoWorkspace.state[2];
acadoVariables.x[index * 4 + 7] = acadoWorkspace.state[3];
}
}