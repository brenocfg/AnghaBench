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
typedef  enum window_priority { ____Placeholder_window_priority } window_priority ;
typedef  int /*<<< orphan*/ * HWND ;

/* Variables and functions */
 int /*<<< orphan*/ * first_window (int,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/ * next_window (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int window_rating (int /*<<< orphan*/ *,int,char const*,char const*,char const*,int) ; 

HWND find_window(enum window_search_mode mode, enum window_priority priority,
		 const char *class, const char *title, const char *exe)
{
	HWND parent;
	bool use_findwindowex = false;

	HWND window = first_window(mode, &parent, &use_findwindowex);
	HWND best_window = NULL;
	int best_rating = 0x7FFFFFFF;

	if (!class)
		return NULL;

	bool uwp_window = strcmp(class, "Windows.UI.Core.CoreWindow") == 0;

	while (window) {
		int rating = window_rating(window, priority, class, title, exe,
					   uwp_window);
		if (rating < best_rating) {
			best_rating = rating;
			best_window = window;
			if (rating == 0)
				break;
		}

		window = next_window(window, mode, &parent, use_findwindowex);
	}

	return best_window;
}