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
typedef  int /*<<< orphan*/  szTaskmgr ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HICON ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDI_TASKMANAGER ; 
 int /*<<< orphan*/  IDS_APP_TITLE ; 
 int /*<<< orphan*/  LoadIcon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShellAboutW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hInst ; 
 int /*<<< orphan*/  hMainWnd ; 

void OnAbout(void)
{
    WCHAR szTaskmgr[128];
    HICON taskmgrIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_TASKMANAGER));

    LoadStringW(hInst, IDS_APP_TITLE, szTaskmgr, sizeof(szTaskmgr)/sizeof(WCHAR));
    ShellAboutW(hMainWnd, szTaskmgr, 0, taskmgrIcon);
    DeleteObject(taskmgrIcon);
}