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
typedef  int /*<<< orphan*/  PGcancel ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfreeCancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cancelConn ; 
 int /*<<< orphan*/  cancelConnLock ; 

void
ResetCancelConn(void)
{
	PGcancel   *oldCancelConn;

#ifdef WIN32
	EnterCriticalSection(&cancelConnLock);
#endif

	oldCancelConn = cancelConn;
	/* be sure handle_sigint doesn't use pointer while freeing */
	cancelConn = NULL;

	if (oldCancelConn != NULL)
		PQfreeCancel(oldCancelConn);

#ifdef WIN32
	LeaveCriticalSection(&cancelConnLock);
#endif
}