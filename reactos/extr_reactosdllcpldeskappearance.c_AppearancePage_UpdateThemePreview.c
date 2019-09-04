#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ThemeActive; } ;
struct TYPE_4__ {int /*<<< orphan*/  Scheme; scalar_t__ hdcThemePreview; TYPE_2__ ActiveTheme; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ GLOBALS ;

/* Variables and functions */
 scalar_t__ DrawThemePreview (scalar_t__,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_APPEARANCE_PREVIEW ; 
 int /*<<< orphan*/  PVM_SET_HDC_PREVIEW ; 
 int /*<<< orphan*/  PVM_UPDATETHEME ; 
 int /*<<< orphan*/  SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AppearancePage_UpdateThemePreview(HWND hwndDlg, GLOBALS *g)
{
    if (g->ActiveTheme.ThemeActive)
    {
        RECT rcWindow;

        GetClientRect(GetDlgItem(hwndDlg, IDC_APPEARANCE_PREVIEW), &rcWindow);
        if (DrawThemePreview(g->hdcThemePreview, &g->Scheme, &g->ActiveTheme, &rcWindow))
        {
            SendDlgItemMessage(hwndDlg, IDC_APPEARANCE_PREVIEW, PVM_SET_HDC_PREVIEW, 0, (LPARAM)g->hdcThemePreview);
            return;
        }
    }

    SendDlgItemMessage(hwndDlg, IDC_APPEARANCE_PREVIEW, PVM_UPDATETHEME, 0, (LPARAM)&g->Scheme);
    SendDlgItemMessage(hwndDlg, IDC_APPEARANCE_PREVIEW, PVM_SET_HDC_PREVIEW, 0, 0);
}