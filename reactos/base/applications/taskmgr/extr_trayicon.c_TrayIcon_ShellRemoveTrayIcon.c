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
struct TYPE_4__ {int cbSize; int /*<<< orphan*/  uCallbackMessage; scalar_t__ uFlags; scalar_t__ uID; int /*<<< orphan*/  hWnd; } ;
typedef  TYPE_1__ NOTIFYICONDATAW ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  NIM_DELETE ; 
 int /*<<< orphan*/  Shell_NotifyIconW (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  WM_ONTRAYICON ; 
 int /*<<< orphan*/  hMainWnd ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

BOOL TrayIcon_ShellRemoveTrayIcon(void)
{
    NOTIFYICONDATAW nid;
    BOOL            bRetVal;

    memset(&nid, 0, sizeof(NOTIFYICONDATAW));

    nid.cbSize = sizeof(NOTIFYICONDATAW);
    nid.hWnd = hMainWnd;
    nid.uID = 0;
    nid.uFlags = 0;
    nid.uCallbackMessage = WM_ONTRAYICON;

    bRetVal = Shell_NotifyIconW(NIM_DELETE, &nid);

    return bRetVal;
}