#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  hProcess; } ;
struct TYPE_5__ {int cb; int /*<<< orphan*/ * lpReserved2; scalar_t__ cbReserved2; scalar_t__ wShowWindow; scalar_t__ dwFlags; scalar_t__ dwYSize; scalar_t__ dwXSize; scalar_t__ dwY; scalar_t__ dwX; int /*<<< orphan*/ * lpTitle; int /*<<< orphan*/ * lpDesktop; int /*<<< orphan*/ * lpReserved; } ;
typedef  int /*<<< orphan*/  StartupInfo ;
typedef  TYPE_1__ STARTUPINFO ;
typedef  TYPE_2__ PROCESS_INFORMATION ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ CreateProcess (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int GetEnvironmentVariable (char*,char*,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char const*,int) ; 

void shell(int argc, const char *argv[])
{
#if 0
	int pid;
	sig_t (*old1)(), (*old2)();
	char shellnam[40], *shell, *namep;
	union wait status;

	old1 = signal (SIGINT, SIG_IGN);
	old2 = signal (SIGQUIT, SIG_IGN);
	if ((pid = fork()) == 0) {
		for (pid = 3; pid < 20; pid++)
			(void) close(pid);
		(void) signal(SIGINT, SIG_DFL);
		(void) signal(SIGQUIT, SIG_DFL);
		shell = getenv("SHELL");
		if (shell == NULL)
			shell = _PATH_BSHELL;
		namep = rindex(shell,'/');
		if (namep == NULL)
			namep = shell;
		(void) strcpy(shellnam,"-");
		(void) strcat(shellnam, ++namep);
		if (strcmp(namep, "sh") != 0)
			shellnam[0] = '+';
		if (debug) {
			printf ("%s\n", shell);
			(void) fflush (stdout);
		}
		if (argc > 1) {
			execl(shell,shellnam,"-c",altarg,(char *)0);
		}
		else {
			execl(shell,shellnam,(char *)0);
		}
		perror(shell);
		code = -1;
		exit(1);
		}
	if (pid > 0)
		while (wait(&status) != pid)
			;
	(void) signal(SIGINT, old1);
	(void) signal(SIGQUIT, old2);
	if (pid == -1) {
		perror("Try again later");
		code = -1;
	}
	else {
		code = 0;
	}
#endif

    char *              AppName;
    char                ShellCmd[MAX_PATH];
    char                CmdLine[MAX_PATH];
    int                 i;
    PROCESS_INFORMATION ProcessInformation;
    BOOL                Result;
    STARTUPINFO         StartupInfo;
    char                ShellName[] = "COMSPEC";
    int                 NumBytes;

    NumBytes = GetEnvironmentVariable( ShellName, ShellCmd, MAX_PATH);

    if (NumBytes == 0)
    {
        return;
    }

    AppName = ShellCmd;
    strcpy( CmdLine, ShellCmd );

    if (argc > 1)
    {
        strncat(CmdLine, " /C", MAX_PATH - strlen(CmdLine) - 1);
    }

    for (i=1; i<argc; i++)
    {
        strncat(CmdLine, " ", MAX_PATH - strlen(CmdLine) - 1);
        strncat(CmdLine, argv[i], MAX_PATH - strlen(CmdLine) - 1); 
    }

    StartupInfo.cb          = sizeof( StartupInfo );
    StartupInfo.lpReserved  = NULL;
    StartupInfo.lpDesktop   = NULL;
    StartupInfo.lpTitle     = NULL;
    StartupInfo.dwX         = 0;
    StartupInfo.dwY         = 0;
    StartupInfo.dwXSize     = 0;
    StartupInfo.dwYSize     = 0;
    StartupInfo.dwFlags     = 0;
    StartupInfo.wShowWindow = 0;
    StartupInfo.cbReserved2 = 0;
    StartupInfo.lpReserved2 = NULL;

    Result = CreateProcess( AppName,                // cmd name
                            CmdLine,                // cmd line arguments
                            NULL,
                            NULL,                   // security attributes
                            FALSE,                  // inherit flags
                            0,                      // Creation flags
                            NULL,                   // Environment
                            NULL,                   // Current directory
                            &StartupInfo,           // Startup info structure
                            &ProcessInformation);   // processInfo structure

    if (Result)
    {
        WaitForSingleObject( ProcessInformation.hProcess, 0xffffffff);

        CloseHandle( ProcessInformation.hProcess);
    }
}