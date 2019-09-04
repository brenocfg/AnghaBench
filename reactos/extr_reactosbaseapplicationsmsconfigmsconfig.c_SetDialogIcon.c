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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyIcon (scalar_t__) ; 
 int /*<<< orphan*/  GetModuleHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ICON_BIG ; 
 int /*<<< orphan*/  ICON_SMALL ; 
 int /*<<< orphan*/  IDI_APPICON ; 
 int /*<<< orphan*/  IMAGE_ICON ; 
 scalar_t__ LoadIconW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LoadImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_SETICON ; 
 scalar_t__ hDialogIconBig ; 
 scalar_t__ hDialogIconSmall ; 
 int /*<<< orphan*/  uXIcon ; 
 int /*<<< orphan*/  uYIcon ; 

__attribute__((used)) static
VOID
SetDialogIcon(HWND hDlg)
{
    if (hDialogIconBig) DestroyIcon(hDialogIconBig);
    if (hDialogIconSmall) DestroyIcon(hDialogIconSmall);

    hDialogIconBig = LoadIconW(GetModuleHandle(NULL),
                               MAKEINTRESOURCE(IDI_APPICON));
    hDialogIconSmall = LoadImage(GetModuleHandle(NULL),
                                 MAKEINTRESOURCE(IDI_APPICON),
                                 IMAGE_ICON,
                                 uXIcon,
                                 uYIcon,
                                 0);
    SendMessage(hDlg,
                WM_SETICON,
                ICON_BIG,
                (LPARAM)hDialogIconBig);
    SendMessage(hDlg,
                WM_SETICON,
                ICON_SMALL,
                (LPARAM)hDialogIconSmall);
}