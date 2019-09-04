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
struct input_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ TPACPI_LIFE_EXITING ; 
 int hotkey_driver_mask ; 
 int /*<<< orphan*/  hotkey_poll_setup_safe (int) ; 
 int hotkey_source_mask ; 
 scalar_t__ tpacpi_lifecycle ; 

__attribute__((used)) static void hotkey_inputdev_close(struct input_dev *dev)
{
	/* disable hotkey polling when possible */
	if (tpacpi_lifecycle != TPACPI_LIFE_EXITING &&
	    !(hotkey_source_mask & hotkey_driver_mask))
		hotkey_poll_setup_safe(false);
}