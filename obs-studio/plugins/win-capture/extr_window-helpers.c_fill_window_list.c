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
typedef  int /*<<< orphan*/  obs_property_t ;
typedef  enum window_search_mode { ____Placeholder_window_search_mode } window_search_mode ;
typedef  int /*<<< orphan*/  add_window_cb ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 int /*<<< orphan*/  add_window (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ first_window (int,scalar_t__*,int*) ; 
 scalar_t__ next_window (scalar_t__,int,scalar_t__*,int) ; 

void fill_window_list(obs_property_t *p, enum window_search_mode mode,
		      add_window_cb callback)
{
	HWND parent;
	bool use_findwindowex = false;

	HWND window = first_window(mode, &parent, &use_findwindowex);

	while (window) {
		add_window(p, window, callback);
		window = next_window(window, mode, &parent, use_findwindowex);
	}
}