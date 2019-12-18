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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/ * GetCommandLineW () ; 
 int /*<<< orphan*/  GetModuleFileNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetEnvironmentVariableW (char*,char*) ; 
 int cr_runproc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcscpy (scalar_t__,char*) ; 
 scalar_t__ wcsrchr (int /*<<< orphan*/ *,char) ; 

int wmain(int argc, wchar_t **argv, wchar_t **envp)
{
    wchar_t *cmd;
    wchar_t exe[MAX_PATH];

    cmd = GetCommandLineW();
    GetModuleFileNameW(NULL, exe, MAX_PATH);
    wcscpy(wcsrchr(exe, '.') + 1, L"exe");

    // Set an environment variable so the child process can tell whether it
    // was started from this wrapper and attach to the console accordingly
    SetEnvironmentVariableW(L"_started_from_console", L"yes");

    return cr_runproc(exe, cmd);
}