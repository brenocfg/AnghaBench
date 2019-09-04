#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_3__ {int bottom; int top; int /*<<< orphan*/  right; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 int /*<<< orphan*/  DefWindowProcW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetClientRect (scalar_t__,TYPE_1__*) ; 
 scalar_t__ GetDlgItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_EDITOR ; 
 int /*<<< orphan*/  IDC_PREVIEW ; 
 int /*<<< orphan*/  IDC_REBAR ; 
 int /*<<< orphan*/  IDC_RULER ; 
 int /*<<< orphan*/  IDC_STATUSBAR ; 
 scalar_t__ IsWindowVisible (scalar_t__) ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MoveWindow (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_GETBARHEIGHT ; 
 int SendMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_SIZE ; 
 scalar_t__ preview_isactive () ; 
 int /*<<< orphan*/  redraw_ruler (scalar_t__) ; 

__attribute__((used)) static LRESULT OnSize( HWND hWnd, WPARAM wParam, LPARAM lParam )
{
    int nStatusSize = 0;
    RECT rc;
    HWND hwndEditor = preview_isactive() ? GetDlgItem(hWnd, IDC_PREVIEW) : GetDlgItem(hWnd, IDC_EDITOR);
    HWND hwndStatusBar = GetDlgItem(hWnd, IDC_STATUSBAR);
    HWND hwndReBar = GetDlgItem(hWnd, IDC_REBAR);
    HWND hRulerWnd = GetDlgItem(hwndReBar, IDC_RULER);
    int rebarHeight = 0;

    if (hwndStatusBar)
    {
        SendMessageW(hwndStatusBar, WM_SIZE, 0, 0);
        if (IsWindowVisible(hwndStatusBar))
        {
            GetClientRect(hwndStatusBar, &rc);
            nStatusSize = rc.bottom - rc.top;
        } else
        {
            nStatusSize = 0;
        }
    }
    if (hwndReBar)
    {
        rebarHeight = SendMessageW(hwndReBar, RB_GETBARHEIGHT, 0, 0);

        MoveWindow(hwndReBar, 0, 0, LOWORD(lParam), rebarHeight, TRUE);
    }
    if (hwndEditor)
    {
        GetClientRect(hWnd, &rc);
        MoveWindow(hwndEditor, 0, rebarHeight, rc.right, rc.bottom-nStatusSize-rebarHeight, TRUE);
    }

    redraw_ruler(hRulerWnd);

    return DefWindowProcW(hWnd, WM_SIZE, wParam, lParam);
}