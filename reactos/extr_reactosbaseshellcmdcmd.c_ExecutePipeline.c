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
typedef  int /*<<< orphan*/  PARSED_COMMAND ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  nErrorLevel ; 

__attribute__((used)) static INT
ExecutePipeline(PARSED_COMMAND *Cmd)
{
#ifdef FEATURE_REDIRECTION
    HANDLE hInput = NULL;
    HANDLE hOldConIn = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hOldConOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hProcess[MAXIMUM_WAIT_OBJECTS];
    INT nProcesses = 0;
    DWORD dwExitCode;

    /* Do all but the last pipe command */
    do
    {
        HANDLE hPipeRead, hPipeWrite;
        if (nProcesses > (MAXIMUM_WAIT_OBJECTS - 2))
        {
            error_too_many_parameters(_T("|"));
            goto failed;
        }

        /* Create the pipe that this process will write into.
         * Make the handles non-inheritable initially, because this
         * process shouldn't inherit the reading handle. */
        if (!CreatePipe(&hPipeRead, &hPipeWrite, NULL, 0))
        {
            error_no_pipe();
            goto failed;
        }

        /* The writing side of the pipe is STDOUT for this process */
        SetHandleInformation(hPipeWrite, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
        SetStdHandle(STD_OUTPUT_HANDLE, hPipeWrite);

        /* Execute it (error check is done later for easier cleanup) */
        hProcess[nProcesses] = ExecuteAsync(Cmd->Subcommands);
        CloseHandle(hPipeWrite);
        if (hInput)
            CloseHandle(hInput);

        /* The reading side of the pipe will be STDIN for the next process */
        SetHandleInformation(hPipeRead, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
        SetStdHandle(STD_INPUT_HANDLE, hPipeRead);
        hInput = hPipeRead;

        if (!hProcess[nProcesses])
            goto failed;
        nProcesses++;

        Cmd = Cmd->Subcommands->Next;
    } while (Cmd->Type == C_PIPE);

    /* The last process uses the original STDOUT */
    SetStdHandle(STD_OUTPUT_HANDLE, hOldConOut);
    hProcess[nProcesses] = ExecuteAsync(Cmd);
    if (!hProcess[nProcesses])
        goto failed;
    nProcesses++;
    CloseHandle(hInput);
    SetStdHandle(STD_INPUT_HANDLE, hOldConIn);

    /* Wait for all processes to complete */
    EnterCriticalSection(&ChildProcessRunningLock);
    WaitForMultipleObjects(nProcesses, hProcess, TRUE, INFINITE);
    LeaveCriticalSection(&ChildProcessRunningLock);

    /* Use the exit code of the last process in the pipeline */
    GetExitCodeProcess(hProcess[nProcesses - 1], &dwExitCode);
    nErrorLevel = (INT)dwExitCode;

    while (--nProcesses >= 0)
        CloseHandle(hProcess[nProcesses]);
    return nErrorLevel;

failed:
    if (hInput)
        CloseHandle(hInput);
    while (--nProcesses >= 0)
    {
        TerminateProcess(hProcess[nProcesses], 0);
        CloseHandle(hProcess[nProcesses]);
    }
    SetStdHandle(STD_INPUT_HANDLE, hOldConIn);
    SetStdHandle(STD_OUTPUT_HANDLE, hOldConOut);
#endif

    return nErrorLevel;
}