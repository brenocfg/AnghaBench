#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  si ;
typedef  int /*<<< orphan*/  pi ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int cb; int /*<<< orphan*/  hThread; int /*<<< orphan*/  hProcess; int /*<<< orphan*/  wShowWindow; int /*<<< orphan*/  dwFlags; } ;
typedef  TYPE_1__ STARTUPINFOW ;
typedef  TYPE_1__ PROCESS_INFORMATION ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ CreateProcessAsUserW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ DuplicateTokenEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExpandEnvironmentStringsW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  GetLastError () ; 
 int MAX_PATH ; 
 scalar_t__ OpenProcessToken (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STARTF_USESHOWWINDOW ; 
 int /*<<< orphan*/  SW_SHOWNORMAL ; 
 int /*<<< orphan*/  SecurityIdentification ; 
 int /*<<< orphan*/  TOKEN_ALL_ACCESS ; 
 int TOKEN_DUPLICATE ; 
 int TOKEN_QUERY ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  TokenPrimary ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 

BOOL LaunchProcess(LPCWSTR lpProcessName)
{
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    HANDLE hUserToken, hProcessToken;
    BOOL bSuccess;
    WCHAR ExpandedCmdLine[MAX_PATH];

    /* Expand the process path string */
    ExpandEnvironmentStringsW(lpProcessName, ExpandedCmdLine, ARRAYSIZE(ExpandedCmdLine));

    ZeroMemory(&pi, sizeof(pi));
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_SHOWNORMAL;

    /* Get the token of the parent (current) process of the application */
    bSuccess = OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_DUPLICATE, &hUserToken);
    if (!bSuccess)
    {
        DPRINT("OpenProcessToken() failed with error -> %lu\n", GetLastError());
        return FALSE;
    }

    /* Duplicate a new token so that we can use it to create our process */
    bSuccess = DuplicateTokenEx(hUserToken, TOKEN_ALL_ACCESS, NULL, SecurityIdentification, TokenPrimary, &hProcessToken);
    if (!bSuccess)
    {
        DPRINT("DuplicateTokenEx() failed with error -> %lu\n", GetLastError());
        CloseHandle(hUserToken);
        return FALSE;
    }

    /* Finally create the process */
    bSuccess = CreateProcessAsUserW(hProcessToken,
                                    NULL,
                                    ExpandedCmdLine,
                                    NULL,
                                    NULL,
                                    FALSE,
                                    0, // DETACHED_PROCESS, NORMAL_PRIORITY_CLASS
                                    NULL,
                                    NULL,
                                    &si,
                                    &pi);

    if (!bSuccess)
    {
        DPRINT("CreateProcessAsUserW() failed with error -> %lu\n", GetLastError());
        CloseHandle(hUserToken);
        CloseHandle(hProcessToken);
        return FALSE;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(hUserToken);
    CloseHandle(hProcessToken);
    return TRUE;
}