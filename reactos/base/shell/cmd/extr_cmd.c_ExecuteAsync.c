#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * hProcess; int /*<<< orphan*/  hThread; } ;
struct TYPE_6__ {int cb; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__ STARTUPINFO ;
typedef  TYPE_2__ PROCESS_INFORMATION ;
typedef  int /*<<< orphan*/  PARSED_COMMAND ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int CMDLINE_LENGTH ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateProcess (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ErrorMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetModuleFileName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * Unparse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/ * _stpcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tcscpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error_out_of_memory () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HANDLE
ExecuteAsync(PARSED_COMMAND *Cmd)
{
    TCHAR CmdPath[MAX_PATH];
    TCHAR CmdParams[CMDLINE_LENGTH], *ParamsEnd;
    STARTUPINFO stui;
    PROCESS_INFORMATION prci;

    /* Get the path to cmd.exe */
    GetModuleFileName(NULL, CmdPath, ARRAYSIZE(CmdPath));

    /* Build the parameter string to pass to cmd.exe */
    ParamsEnd = _stpcpy(CmdParams, _T("/S/D/C\""));
    ParamsEnd = Unparse(Cmd, ParamsEnd, &CmdParams[CMDLINE_LENGTH - 2]);
    if (!ParamsEnd)
    {
        error_out_of_memory();
        return NULL;
    }
    _tcscpy(ParamsEnd, _T("\""));

    memset(&stui, 0, sizeof stui);
    stui.cb = sizeof(STARTUPINFO);
    if (!CreateProcess(CmdPath, CmdParams, NULL, NULL, TRUE, 0,
                       NULL, NULL, &stui, &prci))
    {
        ErrorMessage(GetLastError(), NULL);
        return NULL;
    }

    CloseHandle(prci.hThread);
    return prci.hProcess;
}