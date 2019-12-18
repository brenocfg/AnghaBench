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
typedef  int /*<<< orphan*/ * Operator ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * compatible_oper (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  oprid (int /*<<< orphan*/ *) ; 

Oid
compatible_oper_opid(List *op, Oid arg1, Oid arg2, bool noError)
{
	Operator	optup;
	Oid			result;

	optup = compatible_oper(NULL, op, arg1, arg2, noError, -1);
	if (optup != NULL)
	{
		result = oprid(optup);
		ReleaseSysCache(optup);
		return result;
	}
	return InvalidOid;
}