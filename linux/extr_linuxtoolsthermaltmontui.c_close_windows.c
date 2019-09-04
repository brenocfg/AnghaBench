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

/* Variables and functions */
 int /*<<< orphan*/  close_panel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_window (scalar_t__) ; 
 scalar_t__ control_window ; 
 scalar_t__ cooling_device_window ; 
 int /*<<< orphan*/  data_panel ; 
 int /*<<< orphan*/  dialogue_panel ; 
 scalar_t__ dialogue_window ; 
 scalar_t__ status_bar_window ; 
 scalar_t__ thermal_data_window ; 
 scalar_t__ title_bar_window ; 
 scalar_t__ tui_disabled ; 
 scalar_t__ tz_sensor_window ; 

void close_windows(void)
{
	if (tui_disabled)
		return;
	/* must delete panels before their attached windows */
	if (dialogue_window)
		close_panel(dialogue_panel);
	if (cooling_device_window)
		close_panel(data_panel);

	close_window(title_bar_window);
	close_window(tz_sensor_window);
	close_window(status_bar_window);
	close_window(cooling_device_window);
	close_window(control_window);
	close_window(thermal_data_window);
	close_window(dialogue_window);

}