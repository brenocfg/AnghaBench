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
typedef  enum window_search_mode { ____Placeholder_window_search_mode } window_search_mode ;
struct TYPE_3__ {scalar_t__ bottom; scalar_t__ right; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int DWORD ;

/* Variables and functions */
 int EXCLUDE_MINIMIZED ; 
 int /*<<< orphan*/  GWL_EXSTYLE ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ GetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IsIconic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsWindowVisible (int /*<<< orphan*/ ) ; 
 int WS_CHILD ; 
 int WS_EX_TOOLWINDOW ; 

__attribute__((used)) static bool check_window_valid(HWND window, enum window_search_mode mode)
{
	DWORD styles, ex_styles;
	RECT rect;

	if (!IsWindowVisible(window) ||
	    (mode == EXCLUDE_MINIMIZED && IsIconic(window)))
		return false;

	GetClientRect(window, &rect);
	styles = (DWORD)GetWindowLongPtr(window, GWL_STYLE);
	ex_styles = (DWORD)GetWindowLongPtr(window, GWL_EXSTYLE);

	if (ex_styles & WS_EX_TOOLWINDOW)
		return false;
	if (styles & WS_CHILD)
		return false;
	if (mode == EXCLUDE_MINIMIZED && (rect.bottom == 0 || rect.right == 0))
		return false;

	return true;
}