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
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CONV_LPARAMTOPOINT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ClientToScreen (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDC_COLOR_RES ; 
 int /*<<< orphan*/  IDC_COLOR_RESULT ; 
 int /*<<< orphan*/  PostMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PtInRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_COMMAND ; 

__attribute__((used)) static BOOL CC_MouseCheckResultWindow( HWND hDlg, LPARAM lParam )
{
 HWND hwnd;
 POINT point;
 RECT rect;

 CONV_LPARAMTOPOINT(lParam, &point);
 ClientToScreen(hDlg, &point);
 hwnd = GetDlgItem(hDlg, IDC_COLOR_RESULT);
 GetWindowRect(hwnd, &rect);
 if (PtInRect(&rect, point))
 {
  PostMessageA(hDlg, WM_COMMAND, IDC_COLOR_RES, 0);
  return TRUE;
 }
 return FALSE;
}