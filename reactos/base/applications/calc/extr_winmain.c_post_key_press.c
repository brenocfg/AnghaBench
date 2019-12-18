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
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_2__ {int /*<<< orphan*/  hWnd; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int LRESULT ;
typedef  int LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  BM_CLICK ; 
 int /*<<< orphan*/  BM_SETSTATE ; 
 scalar_t__ BS_DEFPUSHBUTTON ; 
 scalar_t__ BS_OWNERDRAW ; 
 scalar_t__ BS_PUSHBUTTON ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetClassName (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsWindowEnabled (int /*<<< orphan*/ ) ; 
 int KEY_IS_UP ; 
 int KEY_WAS_DOWN ; 
 int /*<<< orphan*/  PostMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIZEOF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WC_BUTTON ; 
 int /*<<< orphan*/  _tcscmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ calc ; 

__attribute__((used)) static LRESULT post_key_press(LPARAM lParam, WORD idc)
{
    HWND  hCtlWnd = GetDlgItem(calc.hWnd,idc);
    TCHAR ClassName[64];

    /* check if the key is enabled! */
    if (!IsWindowEnabled(hCtlWnd))
        return 1;

    if (!GetClassName(hCtlWnd, ClassName, SIZEOF(ClassName)))
        return 1;

    if (!_tcscmp(ClassName, WC_BUTTON)) {
        DWORD dwStyle = GetWindowLongPtr(hCtlWnd, GWL_STYLE) & 0xF;

        /* Set states for press/release, but only for push buttons */
        if (dwStyle == BS_PUSHBUTTON || dwStyle == BS_DEFPUSHBUTTON || dwStyle == BS_OWNERDRAW) {
            if (!(lParam & KEY_WAS_DOWN)) {
                PostMessage(hCtlWnd, BM_SETSTATE, 1, 0);
            } else
            if ((lParam & KEY_IS_UP)) {
                PostMessage(hCtlWnd, BM_SETSTATE, 0, 0);
                PostMessage(hCtlWnd, BM_CLICK, 0, 0);
            }
            return 1;
        }
    }
    /* default action: simple click event at key release */
    if ((lParam & KEY_IS_UP)) {
        PostMessage(hCtlWnd, BM_CLICK, 0, 0);
    }
    return 1;
}