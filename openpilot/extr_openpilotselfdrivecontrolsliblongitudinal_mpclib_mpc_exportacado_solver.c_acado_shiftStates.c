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
acadoVariables.x[index * 3] = acadoVariables.x[index * 3 + 3];
acadoVariables.x[index * 3 + 1] = acadoVariables.x[index * 3 + 4];
acadoVariables.x[index * 3 + 2] = acadoVariables.x[index * 3 + 5];
}

if (strategy == 1 && xEnd != 0)
{
acadoVariables.x[60] = xEnd[0];
acadoVariables.x[61] = xEnd[1];
acadoVariables.x[62] = xEnd[2];
}
else if (strategy == 2) 
{
acadoWorkspace.state[0] = acadoVariables.x[60];
acadoWorkspace.state[1] = acadoVariables.x[61];
acadoWorkspace.state[2] = acadoVariables.x[62];
if (uEnd != 0)
{
acadoWorkspace.state[15] = uEnd[0];
}
else
{
acadoWorkspace.state[15] = acadoVariables.u[19];
}
acadoWorkspace.state[16] = acadoVariables.od[40];
acadoWorkspace.state[17] = acadoVariables.od[41];

acado_integrate(acadoWorkspace.state, 1, 19);

acadoVariables.x[60] = acadoWorkspace.state[0];
acadoVariables.x[61] = acadoWorkspace.state[1];
acadoVariables.x[62] = acadoWorkspace.state[2];
}
}