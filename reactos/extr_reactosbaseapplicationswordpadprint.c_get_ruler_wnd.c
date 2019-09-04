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
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_REBAR ; 
 int /*<<< orphan*/  IDC_RULER ; 

__attribute__((used)) static HWND get_ruler_wnd(HWND hMainWnd)
{
    return GetDlgItem(GetDlgItem(hMainWnd, IDC_REBAR), IDC_RULER);
}