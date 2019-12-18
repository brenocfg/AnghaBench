#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* myAH; } ;
struct TYPE_4__ {int /*<<< orphan*/ * connCancel; } ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  int /*<<< orphan*/  PGcancel ;
typedef  TYPE_1__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ GetCurrentThreadId () ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfreeCancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQgetCancel (int /*<<< orphan*/ *) ; 
 scalar_t__ mainThreadId ; 
 int /*<<< orphan*/  setup_cancel_handler () ; 
 TYPE_2__ signal_info ; 
 int /*<<< orphan*/  signal_info_lock ; 

void
set_archive_cancel_info(ArchiveHandle *AH, PGconn *conn)
{
	PGcancel   *oldConnCancel;

	/*
	 * Activate the interrupt handler if we didn't yet in this process.  On
	 * Windows, this also initializes signal_info_lock; therefore it's
	 * important that this happen at least once before we fork off any
	 * threads.
	 */
	setup_cancel_handler();

	/*
	 * On Unix, we assume that storing a pointer value is atomic with respect
	 * to any possible signal interrupt.  On Windows, use a critical section.
	 */

#ifdef WIN32
	EnterCriticalSection(&signal_info_lock);
#endif

	/* Free the old one if we have one */
	oldConnCancel = AH->connCancel;
	/* be sure interrupt handler doesn't use pointer while freeing */
	AH->connCancel = NULL;

	if (oldConnCancel != NULL)
		PQfreeCancel(oldConnCancel);

	/* Set the new one if specified */
	if (conn)
		AH->connCancel = PQgetCancel(conn);

	/*
	 * On Unix, there's only ever one active ArchiveHandle per process, so we
	 * can just set signal_info.myAH unconditionally.  On Windows, do that
	 * only in the main thread; worker threads have to make sure their
	 * ArchiveHandle appears in the pstate data, which is dealt with in
	 * RunWorker().
	 */
#ifndef WIN32
	signal_info.myAH = AH;
#else
	if (mainThreadId == GetCurrentThreadId())
		signal_info.myAH = AH;
#endif

#ifdef WIN32
	LeaveCriticalSection(&signal_info_lock);
#endif
}