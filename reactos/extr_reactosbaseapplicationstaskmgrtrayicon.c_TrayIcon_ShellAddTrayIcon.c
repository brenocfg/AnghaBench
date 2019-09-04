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
typedef  int /*<<< orphan*/  szMsg ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int cbSize; int uFlags; int /*<<< orphan*/  szTip; int /*<<< orphan*/ * hIcon; int /*<<< orphan*/  uCallbackMessage; scalar_t__ uID; int /*<<< orphan*/  hWnd; } ;
typedef  TYPE_1__ NOTIFYICONDATAW ;
typedef  int /*<<< orphan*/ * HICON ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyIcon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetModuleHandleW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDS_MSG_TRAYICONCPUUSAGE ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int NIF_ICON ; 
 int NIF_MESSAGE ; 
 int NIF_TIP ; 
 int /*<<< orphan*/  NIM_ADD ; 
 int /*<<< orphan*/  PerfDataGetProcessorUsage () ; 
 int /*<<< orphan*/  Shell_NotifyIconW (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * TrayIcon_GetProcessorUsageIcon () ; 
 int /*<<< orphan*/  WM_ONTRAYICON ; 
 int /*<<< orphan*/  hMainWnd ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wsprintfW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BOOL TrayIcon_ShellAddTrayIcon(void)
{
    NOTIFYICONDATAW nid;
    HICON           hIcon = NULL;
    BOOL            bRetVal;
    WCHAR           szMsg[64];

    memset(&nid, 0, sizeof(NOTIFYICONDATAW));

    hIcon = TrayIcon_GetProcessorUsageIcon();

    nid.cbSize = sizeof(NOTIFYICONDATAW);
    nid.hWnd = hMainWnd;
    nid.uID = 0;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_ONTRAYICON;
    nid.hIcon = hIcon;


    LoadStringW( GetModuleHandleW(NULL), IDS_MSG_TRAYICONCPUUSAGE, szMsg, sizeof(szMsg) / sizeof(szMsg[0]));
    wsprintfW(nid.szTip, szMsg, PerfDataGetProcessorUsage());

    bRetVal = Shell_NotifyIconW(NIM_ADD, &nid);

    if (hIcon)
        DestroyIcon(hIcon);

    return bRetVal;
}