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
acadoWorkspace.state[0] = acadoVariables.x[index * 3];
acadoWorkspace.state[1] = acadoVariables.x[index * 3 + 1];
acadoWorkspace.state[2] = acadoVariables.x[index * 3 + 2];
acadoWorkspace.state[15] = acadoVariables.u[index];
acadoWorkspace.state[16] = acadoVariables.od[index * 2];
acadoWorkspace.state[17] = acadoVariables.od[index * 2 + 1];

acado_integrate(acadoWorkspace.state, index == 0, index);

acadoVariables.x[index * 3 + 3] = acadoWorkspace.state[0];
acadoVariables.x[index * 3 + 4] = acadoWorkspace.state[1];
acadoVariables.x[index * 3 + 5] = acadoWorkspace.state[2];
}
}