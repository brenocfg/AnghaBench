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
typedef  int /*<<< orphan*/  real_t ;

/* Variables and functions */

real_t* acado_getVariablesX0( )
{
#if ACADO_INITIAL_VALUE_FIXED
	return acadoVariables.x0;
#else
	return 0;
#endif
}