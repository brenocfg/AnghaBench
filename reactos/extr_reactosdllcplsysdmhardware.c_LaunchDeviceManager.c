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
typedef  int /*<<< orphan*/  (* PDEVMGREXEC ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ ) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LoadLibrary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  _TEXT (char*) ; 
 int /*<<< orphan*/  hApplet ; 

__attribute__((used)) static BOOL
LaunchDeviceManager(HWND hWndParent)
{
/* Hack for ROS to start our devmgmt until we have MMC */
#ifdef __REACTOS__
    return ((INT_PTR)ShellExecuteW(NULL, L"open", L"devmgmt.exe", NULL, NULL, SW_SHOWNORMAL) > 32);
#else
    HMODULE hDll;
    PDEVMGREXEC DevMgrExec;
    BOOL Ret;

    hDll = LoadLibrary(_TEXT("devmgr.dll"));
    if(!hDll)
        return FALSE;

    DevMgrExec = (PDEVMGREXEC)GetProcAddress(hDll, "DeviceManager_ExecuteW");
    if(!DevMgrExec)
    {
        FreeLibrary(hDll);
        return FALSE;
    }

    /* Run the Device Manager */
    Ret = DevMgrExec(hWndParent, hApplet, NULL /* ??? */, SW_SHOW);
    FreeLibrary(hDll);
    return Ret;
#endif /* __REACTOS__ */
}