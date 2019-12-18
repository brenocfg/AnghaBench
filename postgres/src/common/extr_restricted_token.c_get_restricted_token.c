#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pi ;
struct TYPE_4__ {int /*<<< orphan*/  hProcess; int /*<<< orphan*/  hThread; } ;
typedef  TYPE_1__ PROCESS_INFORMATION ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateRestrictedProcess (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  GetCommandLine () ; 
 int /*<<< orphan*/  GetExitCodeProcess (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/  pg_log_error (char*,int /*<<< orphan*/ ) ; 
 char* pg_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putenv (char*) ; 
 int /*<<< orphan*/ * restrict_env ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

void
get_restricted_token(void)
{
#ifdef WIN32
	HANDLE		restrictedToken;

	/*
	 * Before we execute another program, make sure that we are running with a
	 * restricted token. If not, re-execute ourselves with one.
	 */

	if ((restrict_env = getenv("PG_RESTRICT_EXEC")) == NULL
		|| strcmp(restrict_env, "1") != 0)
	{
		PROCESS_INFORMATION pi;
		char	   *cmdline;

		ZeroMemory(&pi, sizeof(pi));

		cmdline = pg_strdup(GetCommandLine());

		putenv("PG_RESTRICT_EXEC=1");

		if ((restrictedToken = CreateRestrictedProcess(cmdline, &pi)) == 0)
		{
			pg_log_error("could not re-execute with restricted token: error code %lu", GetLastError());
		}
		else
		{
			/*
			 * Successfully re-execed. Now wait for child process to capture
			 * exitcode.
			 */
			DWORD		x;

			CloseHandle(restrictedToken);
			CloseHandle(pi.hThread);
			WaitForSingleObject(pi.hProcess, INFINITE);

			if (!GetExitCodeProcess(pi.hProcess, &x))
			{
				pg_log_error("could not get exit code from subprocess: error code %lu", GetLastError());
				exit(1);
			}
			exit(x);
		}
	}
#endif
}