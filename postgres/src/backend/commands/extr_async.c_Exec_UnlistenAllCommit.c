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

/* Variables and functions */
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  MyProcPid ; 
 int /*<<< orphan*/  NIL ; 
 scalar_t__ Trace_notify ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_free_deep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listenChannels ; 

__attribute__((used)) static void
Exec_UnlistenAllCommit(void)
{
	if (Trace_notify)
		elog(DEBUG1, "Exec_UnlistenAllCommit(%d)", MyProcPid);

	list_free_deep(listenChannels);
	listenChannels = NIL;
}