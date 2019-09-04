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
typedef  int /*<<< orphan*/  tnid ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {int cbSize; int uID; int uFlags; int /*<<< orphan*/  szTip; int /*<<< orphan*/  hIcon; int /*<<< orphan*/  uCallbackMessage; int /*<<< orphan*/  hWnd; } ;
typedef  TYPE_1__ NOTIFYICONDATA ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateTrayIcon (int /*<<< orphan*/ ) ; 
 int NIF_ICON ; 
 int NIF_MESSAGE ; 
 int NIF_TIP ; 
 int /*<<< orphan*/  NIM_MODIFY ; 
 int /*<<< orphan*/  Shell_NotifyIcon (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StringCchCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_NOTIFYICONMSG ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static VOID
UpdateTrayIcon(HWND hwnd, LPTSTR szLCID, LPTSTR szName)
{
    NOTIFYICONDATA tnid;

    memset(&tnid, 0, sizeof(tnid));
    tnid.cbSize = sizeof(NOTIFYICONDATA);
    tnid.hWnd = hwnd;
    tnid.uID = 1;
    tnid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    tnid.uCallbackMessage = WM_NOTIFYICONMSG;
    tnid.hIcon = CreateTrayIcon(szLCID);

    StringCchCopy(tnid.szTip, ARRAYSIZE(tnid.szTip), szName);

    Shell_NotifyIcon(NIM_MODIFY, &tnid);
}