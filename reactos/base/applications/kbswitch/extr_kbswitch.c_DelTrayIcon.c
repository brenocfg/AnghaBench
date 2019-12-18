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
struct TYPE_4__ {int cbSize; int uID; int /*<<< orphan*/  hWnd; } ;
typedef  TYPE_1__ NOTIFYICONDATA ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  NIM_DELETE ; 
 int /*<<< orphan*/  Shell_NotifyIcon (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static VOID
DelTrayIcon(HWND hwnd)
{
    NOTIFYICONDATA tnid;

    memset(&tnid, 0, sizeof(tnid));
    tnid.cbSize = sizeof(NOTIFYICONDATA);
    tnid.hWnd = hwnd;
    tnid.uID = 1;

    Shell_NotifyIcon(NIM_DELETE, &tnid);
}