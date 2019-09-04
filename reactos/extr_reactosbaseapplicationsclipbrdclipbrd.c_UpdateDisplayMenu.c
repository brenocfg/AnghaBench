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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_2__ {int /*<<< orphan*/  hInstance; int /*<<< orphan*/  hMainWnd; int /*<<< orphan*/  hMenu; } ;
typedef  int /*<<< orphan*/  HMENU ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AppendMenuW (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ CMD_AUTOMATIC ; 
 int /*<<< orphan*/  CloseClipboard () ; 
 scalar_t__ CountClipboardFormats () ; 
 int /*<<< orphan*/  DISPLAY_MENU_POS ; 
 int /*<<< orphan*/  DeleteMenu (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ EnumClipboardFormats (scalar_t__) ; 
 int GetMenuItemCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSubMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ Globals ; 
 scalar_t__ IsClipboardFormatSupported (scalar_t__) ; 
 int /*<<< orphan*/  MAX_FMT_NAME_LEN ; 
 int /*<<< orphan*/  MF_BYPOSITION ; 
 int MF_GRAYED ; 
 int MF_SEPARATOR ; 
 int MF_STRING ; 
 int /*<<< orphan*/  OpenClipboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RetrieveClipboardFormatName (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void UpdateDisplayMenu(void)
{
    UINT uFormat;
    HMENU hMenu;
    WCHAR szFormatName[MAX_FMT_NAME_LEN + 1];

    hMenu = GetSubMenu(Globals.hMenu, DISPLAY_MENU_POS);

    while (GetMenuItemCount(hMenu) > 1)
    {
        DeleteMenu(hMenu, 1, MF_BYPOSITION);
    }

    if (CountClipboardFormats() == 0)
        return;

    if (!OpenClipboard(Globals.hMainWnd))
        return;

    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);

    /* Display the supported clipboard formats first */
    for (uFormat = EnumClipboardFormats(0); uFormat;
         uFormat = EnumClipboardFormats(uFormat))
    {
        if (IsClipboardFormatSupported(uFormat))
        {
            RetrieveClipboardFormatName(Globals.hInstance, uFormat, TRUE,
                                        szFormatName, ARRAYSIZE(szFormatName));
            AppendMenuW(hMenu, MF_STRING, CMD_AUTOMATIC + uFormat, szFormatName);
        }
    }

    /* Now display the unsupported clipboard formats */
    for (uFormat = EnumClipboardFormats(0); uFormat;
         uFormat = EnumClipboardFormats(uFormat))
    {
        if (!IsClipboardFormatSupported(uFormat))
        {
            RetrieveClipboardFormatName(Globals.hInstance, uFormat, TRUE,
                                        szFormatName, ARRAYSIZE(szFormatName));
            AppendMenuW(hMenu, MF_STRING | MF_GRAYED, 0, szFormatName);
        }
    }

    CloseClipboard();
}