#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  real_t ;
struct TYPE_2__ {int /*<<< orphan*/ * u; } ;

/* Variables and functions */
 TYPE_1__ acadoVariables ; 

real_t* acado_getVariablesU( )
{
	return acadoVariables.u;
}