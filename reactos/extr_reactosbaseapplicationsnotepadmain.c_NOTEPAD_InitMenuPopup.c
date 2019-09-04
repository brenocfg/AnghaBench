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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_2__ {int /*<<< orphan*/  hMainWnd; int /*<<< orphan*/  hEdit; scalar_t__ bShowStatusBar; scalar_t__ bWrapLongLines; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HMENU ;

/* Variables and functions */
 int /*<<< orphan*/  CF_TEXT ; 
 int /*<<< orphan*/  CMD_COPY ; 
 int /*<<< orphan*/  CMD_CUT ; 
 int /*<<< orphan*/  CMD_DELETE ; 
 int /*<<< orphan*/  CMD_PASTE ; 
 int /*<<< orphan*/  CMD_SELECT_ALL ; 
 int /*<<< orphan*/  CMD_STATUSBAR ; 
 int /*<<< orphan*/  CMD_UNDO ; 
 int /*<<< orphan*/  CMD_WRAP ; 
 int /*<<< orphan*/  CheckMenuItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DrawMenuBar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EM_CANUNDO ; 
 int /*<<< orphan*/  EM_GETSEL ; 
 int /*<<< orphan*/  EnableMenuItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetMenu (int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindowTextLength (int /*<<< orphan*/ ) ; 
 TYPE_1__ Globals ; 
 scalar_t__ HIWORD (int) ; 
 scalar_t__ IsClipboardFormatAvailable (int /*<<< orphan*/ ) ; 
 scalar_t__ LOWORD (int) ; 
 int MF_BYCOMMAND ; 
 int MF_CHECKED ; 
 int MF_ENABLED ; 
 int MF_GRAYED ; 
 int MF_UNCHECKED ; 
 scalar_t__ SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNREFERENCED_PARAMETER (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID NOTEPAD_InitMenuPopup(HMENU menu, LPARAM index)
{
    int enable;

    UNREFERENCED_PARAMETER(index);

    CheckMenuItem(GetMenu(Globals.hMainWnd), CMD_WRAP,
        MF_BYCOMMAND | (Globals.bWrapLongLines ? MF_CHECKED : MF_UNCHECKED));
    if (!Globals.bWrapLongLines)
    {
        CheckMenuItem(GetMenu(Globals.hMainWnd), CMD_STATUSBAR,
            MF_BYCOMMAND | (Globals.bShowStatusBar ? MF_CHECKED : MF_UNCHECKED));
    }
    EnableMenuItem(menu, CMD_UNDO,
        SendMessage(Globals.hEdit, EM_CANUNDO, 0, 0) ? MF_ENABLED : MF_GRAYED);
    EnableMenuItem(menu, CMD_PASTE,
        IsClipboardFormatAvailable(CF_TEXT) ? MF_ENABLED : MF_GRAYED);
    enable = (int) SendMessage(Globals.hEdit, EM_GETSEL, 0, 0);
    enable = (HIWORD(enable) == LOWORD(enable)) ? MF_GRAYED : MF_ENABLED;
    EnableMenuItem(menu, CMD_CUT, enable);
    EnableMenuItem(menu, CMD_COPY, enable);
    EnableMenuItem(menu, CMD_DELETE, enable);

    EnableMenuItem(menu, CMD_SELECT_ALL,
        GetWindowTextLength(Globals.hEdit) ? MF_ENABLED : MF_GRAYED);
    DrawMenuBar(Globals.hMainWnd);
}