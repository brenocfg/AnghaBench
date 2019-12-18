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
typedef  int /*<<< orphan*/  gimple ;

/* Variables and functions */
 int /*<<< orphan*/  BUILT_IN_ALLOCA ; 
 int /*<<< orphan*/  BUILT_IN_ALLOCA_WITH_ALIGN ; 
 scalar_t__ gimple_call_builtin_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_alloca(gimple stmt)
{
	if (gimple_call_builtin_p(stmt, BUILT_IN_ALLOCA))
		return true;

#if BUILDING_GCC_VERSION >= 4007
	if (gimple_call_builtin_p(stmt, BUILT_IN_ALLOCA_WITH_ALIGN))
		return true;
#endif

	return false;
}