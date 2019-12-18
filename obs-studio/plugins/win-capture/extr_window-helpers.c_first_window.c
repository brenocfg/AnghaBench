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
typedef  enum window_search_mode { ____Placeholder_window_search_mode } window_search_mode ;
typedef  int /*<<< orphan*/ * HWND ;

/* Variables and functions */
 int /*<<< orphan*/ * FindWindowEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GW_CHILD ; 
 int /*<<< orphan*/  GetDesktopWindow () ; 
 int /*<<< orphan*/ * GetWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_window_valid (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * get_uwp_actual_window (int /*<<< orphan*/ *) ; 
 scalar_t__ is_uwp_window (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * next_window (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static HWND first_window(enum window_search_mode mode, HWND *parent,
			 bool *use_findwindowex)
{
	HWND window = FindWindowEx(GetDesktopWindow(), NULL, NULL, NULL);

	if (!window) {
		*use_findwindowex = false;
		window = GetWindow(GetDesktopWindow(), GW_CHILD);
	} else {
		*use_findwindowex = true;
	}

	*parent = NULL;

	if (!check_window_valid(window, mode)) {
		window = next_window(window, mode, parent, *use_findwindowex);

		if (!window && *use_findwindowex) {
			*use_findwindowex = false;

			window = GetWindow(GetDesktopWindow(), GW_CHILD);
			if (!check_window_valid(window, mode))
				window = next_window(window, mode, parent,
						     *use_findwindowex);
		}
	}

	if (is_uwp_window(window)) {
		HWND child = get_uwp_actual_window(window);
		if (child) {
			*parent = window;
			return child;
		}
	}

	return window;
}