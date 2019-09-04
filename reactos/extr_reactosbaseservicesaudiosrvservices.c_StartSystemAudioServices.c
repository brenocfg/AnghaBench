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
typedef  int /*<<< orphan*/  SC_HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  OpenSCManager (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_MANAGER_CONNECT ; 
 int /*<<< orphan*/  StartAudioService (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  logmsg (char*,...) ; 

BOOL
StartSystemAudioServices()
{
    SC_HANDLE hSCManager;

    logmsg("Starting system audio services\n");

    hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if (!hSCManager)
    {
        logmsg("Failed to open service manager %x\n", GetLastError());
        return FALSE;
    }

    logmsg("Starting sysaudio service\n");
    StartAudioService(hSCManager, L"sysaudio", 20);
    logmsg("Starting wdmaud service\n");
    StartAudioService(hSCManager, L"wdmaud", 20);

    CloseServiceHandle(hSCManager);
    return TRUE;
}