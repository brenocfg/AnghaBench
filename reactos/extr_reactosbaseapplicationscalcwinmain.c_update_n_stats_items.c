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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  IDC_LIST_STAT ; 
 int /*<<< orphan*/  IDC_TEXT_NITEMS ; 
 int /*<<< orphan*/  LB_GETCOUNT ; 
 unsigned int SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDlgItemText (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _stprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void update_n_stats_items(HWND hWnd, TCHAR *buffer)
{
    unsigned int n = SendDlgItemMessage(hWnd, IDC_LIST_STAT, LB_GETCOUNT, 0, 0); 

    _stprintf(buffer, _T("n=%u"), n);
    SetDlgItemText(hWnd, IDC_TEXT_NITEMS, buffer);
}