#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  hMainWnd; int /*<<< orphan*/  hInstance; } ;
typedef  int /*<<< orphan*/  LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CloseClipboard () ; 
 int /*<<< orphan*/  EmptyClipboard () ; 
 TYPE_1__ Globals ; 
 scalar_t__ IDYES ; 
 int MB_ICONWARNING ; 
 int MB_YESNO ; 
 scalar_t__ MessageBoxRes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OpenClipboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadClipboardFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRING_DELETE_MSG ; 
 int /*<<< orphan*/  STRING_DELETE_TITLE ; 
 int /*<<< orphan*/  ShowLastWin32Error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void LoadClipboardDataFromFile(LPWSTR lpszFileName)
{
    if (MessageBoxRes(Globals.hMainWnd, Globals.hInstance,
                      STRING_DELETE_MSG, STRING_DELETE_TITLE,
                      MB_ICONWARNING | MB_YESNO) != IDYES)
    {
        return;
    }

    if (!OpenClipboard(Globals.hMainWnd))
    {
        ShowLastWin32Error(Globals.hMainWnd);
        return;
    }

    EmptyClipboard();
    ReadClipboardFile(lpszFileName);

    CloseClipboard();
}