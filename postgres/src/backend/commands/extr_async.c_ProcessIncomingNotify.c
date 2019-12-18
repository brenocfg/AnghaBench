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
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  DEBUG1 ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 scalar_t__ Trace_notify ; 
 int /*<<< orphan*/  asyncQueueReadAllNotifications () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ listenChannels ; 
 int notifyInterruptPending ; 
 int /*<<< orphan*/  pq_flush () ; 
 int /*<<< orphan*/  set_ps_display (char*,int) ; 

__attribute__((used)) static void
ProcessIncomingNotify(void)
{
	/* We *must* reset the flag */
	notifyInterruptPending = false;

	/* Do nothing else if we aren't actively listening */
	if (listenChannels == NIL)
		return;

	if (Trace_notify)
		elog(DEBUG1, "ProcessIncomingNotify");

	set_ps_display("notify interrupt", false);

	/*
	 * We must run asyncQueueReadAllNotifications inside a transaction, else
	 * bad things happen if it gets an error.
	 */
	StartTransactionCommand();

	asyncQueueReadAllNotifications();

	CommitTransactionCommand();

	/*
	 * Must flush the notify messages to ensure frontend gets them promptly.
	 */
	pq_flush();

	set_ps_display("idle", false);

	if (Trace_notify)
		elog(DEBUG1, "ProcessIncomingNotify: done");
}