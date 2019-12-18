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
typedef  int /*<<< orphan*/  ModifyTableState ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

void
ExecReScanModifyTable(ModifyTableState *node)
{
	/*
	 * Currently, we don't need to support rescan on ModifyTable nodes. The
	 * semantics of that would be a bit debatable anyway.
	 */
	elog(ERROR, "ExecReScanModifyTable is not implemented");
}