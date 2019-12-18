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
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 scalar_t__ NIL ; 
 int /*<<< orphan*/  SignalBackends () ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 scalar_t__ Trace_notify ; 
 int /*<<< orphan*/  asyncQueueAdvanceTail () ; 
 int /*<<< orphan*/  asyncQueueReadAllNotifications () ; 
 int backendHasSentNotifications ; 
 int backendTryAdvanceTail ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ listenChannels ; 

void
ProcessCompletedNotifies(void)
{
	MemoryContext caller_context;

	/* Nothing to do if we didn't send any notifications */
	if (!backendHasSentNotifications)
		return;

	/*
	 * We reset the flag immediately; otherwise, if any sort of error occurs
	 * below, we'd be locked up in an infinite loop, because control will come
	 * right back here after error cleanup.
	 */
	backendHasSentNotifications = false;

	/*
	 * We must preserve the caller's memory context (probably MessageContext)
	 * across the transaction we do here.
	 */
	caller_context = CurrentMemoryContext;

	if (Trace_notify)
		elog(DEBUG1, "ProcessCompletedNotifies");

	/*
	 * We must run asyncQueueReadAllNotifications inside a transaction, else
	 * bad things happen if it gets an error.
	 */
	StartTransactionCommand();

	/* Send signals to other backends */
	SignalBackends();

	if (listenChannels != NIL)
	{
		/* Read the queue ourselves, and send relevant stuff to the frontend */
		asyncQueueReadAllNotifications();
	}

	/*
	 * If it's time to try to advance the global tail pointer, do that.
	 */
	if (backendTryAdvanceTail)
	{
		backendTryAdvanceTail = false;
		asyncQueueAdvanceTail();
	}

	CommitTransactionCommand();

	MemoryContextSwitchTo(caller_context);

	/* We don't need pq_flush() here since postgres.c will do one shortly */
}