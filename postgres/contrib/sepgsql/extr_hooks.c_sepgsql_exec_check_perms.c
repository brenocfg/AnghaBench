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
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  next_exec_check_perms_hook (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sepgsql_dml_privileges (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool
sepgsql_exec_check_perms(List *rangeTabls, bool abort)
{
	/*
	 * If security provider is stacking and one of them replied 'false' at
	 * least, we don't need to check any more.
	 */
	if (next_exec_check_perms_hook &&
		!(*next_exec_check_perms_hook) (rangeTabls, abort))
		return false;

	if (!sepgsql_dml_privileges(rangeTabls, abort))
		return false;

	return true;
}