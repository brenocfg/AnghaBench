#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ estimate; } ;
typedef  TYPE_1__ eval_const_expressions_context ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 char PROVOLATILE_IMMUTABLE ; 
 char PROVOLATILE_STABLE ; 
 char func_volatile (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ece_function_is_safe(Oid funcid, eval_const_expressions_context *context)
{
	char		provolatile = func_volatile(funcid);

	/*
	 * Ordinarily we are only allowed to simplify immutable functions. But for
	 * purposes of estimation, we consider it okay to simplify functions that
	 * are merely stable; the risk that the result might change from planning
	 * time to execution time is worth taking in preference to not being able
	 * to estimate the value at all.
	 */
	if (provolatile == PROVOLATILE_IMMUTABLE)
		return true;
	if (context->estimate && provolatile == PROVOLATILE_STABLE)
		return true;
	return false;
}