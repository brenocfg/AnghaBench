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
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  InitializeCriticalSection (int /*<<< orphan*/ *) ; 
 int PG_SIGNAL_COUNT ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SetConsoleCtrlHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*,...) ; 
 int /*<<< orphan*/  pg_console_handler ; 
 int /*<<< orphan*/ * pg_signal_array ; 
 int /*<<< orphan*/  pg_signal_crit_sec ; 
 int /*<<< orphan*/ * pg_signal_defaults ; 
 scalar_t__ pg_signal_mask ; 
 scalar_t__ pg_signal_queue ; 
 int /*<<< orphan*/  pg_signal_thread ; 
 int /*<<< orphan*/ * pgwin32_signal_event ; 

void
pgwin32_signal_initialize(void)
{
	int			i;
	HANDLE		signal_thread_handle;

	InitializeCriticalSection(&pg_signal_crit_sec);

	for (i = 0; i < PG_SIGNAL_COUNT; i++)
	{
		pg_signal_array[i] = SIG_DFL;
		pg_signal_defaults[i] = SIG_IGN;
	}
	pg_signal_mask = 0;
	pg_signal_queue = 0;

	/* Create the global event handle used to flag signals */
	pgwin32_signal_event = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (pgwin32_signal_event == NULL)
		ereport(FATAL,
				(errmsg_internal("could not create signal event: error code %lu", GetLastError())));

	/* Create thread for handling signals */
	signal_thread_handle = CreateThread(NULL, 0, pg_signal_thread, NULL, 0, NULL);
	if (signal_thread_handle == NULL)
		ereport(FATAL,
				(errmsg_internal("could not create signal handler thread")));

	/* Create console control handle to pick up Ctrl-C etc */
	if (!SetConsoleCtrlHandler(pg_console_handler, TRUE))
		ereport(FATAL,
				(errmsg_internal("could not set console control handler")));
}