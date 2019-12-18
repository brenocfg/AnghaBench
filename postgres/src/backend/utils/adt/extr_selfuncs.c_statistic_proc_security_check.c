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
struct TYPE_3__ {scalar_t__ acl_ok; } ;
typedef  TYPE_1__ VariableStatData ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_func_leakproof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_func_name (int /*<<< orphan*/ ) ; 

bool
statistic_proc_security_check(VariableStatData *vardata, Oid func_oid)
{
	if (vardata->acl_ok)
		return true;

	if (!OidIsValid(func_oid))
		return false;

	if (get_func_leakproof(func_oid))
		return true;

	ereport(DEBUG2,
			(errmsg_internal("not using statistics because function \"%s\" is not leak-proof",
							 get_func_name(func_oid))));
	return false;
}