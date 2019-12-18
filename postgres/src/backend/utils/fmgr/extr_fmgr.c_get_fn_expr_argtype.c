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
struct TYPE_3__ {int /*<<< orphan*/  fn_expr; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ FmgrInfo ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  get_call_expr_argtype (int /*<<< orphan*/ ,int) ; 

Oid
get_fn_expr_argtype(FmgrInfo *flinfo, int argnum)
{
	/*
	 * can't return anything useful if we have no FmgrInfo or if its fn_expr
	 * node has not been initialized
	 */
	if (!flinfo || !flinfo->fn_expr)
		return InvalidOid;

	return get_call_expr_argtype(flinfo->fn_expr, argnum);
}