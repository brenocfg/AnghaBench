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
typedef  int /*<<< orphan*/  pipename ;
typedef  scalar_t__ pid_t ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 scalar_t__ CreateNamedPipe (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  PIPE_ACCESS_DUPLEX ; 
 int PIPE_READMODE_MESSAGE ; 
 int PIPE_TYPE_MESSAGE ; 
 int /*<<< orphan*/  PIPE_UNLIMITED_INSTANCES ; 
 int PIPE_WAIT ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

HANDLE
pgwin32_create_signal_listener(pid_t pid)
{
	char		pipename[128];
	HANDLE		pipe;

	snprintf(pipename, sizeof(pipename), "\\\\.\\pipe\\pgsignal_%u", (int) pid);

	pipe = CreateNamedPipe(pipename, PIPE_ACCESS_DUPLEX,
						   PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
						   PIPE_UNLIMITED_INSTANCES, 16, 16, 1000, NULL);

	if (pipe == INVALID_HANDLE_VALUE)
		ereport(ERROR,
				(errmsg("could not create signal listener pipe for PID %d: error code %lu",
						(int) pid, GetLastError())));

	return pipe;
}