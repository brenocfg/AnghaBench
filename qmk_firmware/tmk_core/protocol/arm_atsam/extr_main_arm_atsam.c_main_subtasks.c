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
 int /*<<< orphan*/  main_subtask_power_check () ; 
 int /*<<< orphan*/  main_subtask_usb_extra_device () ; 
 int /*<<< orphan*/  main_subtask_usb_state () ; 

void main_subtasks(void) {
    main_subtask_usb_state();
    main_subtask_power_check();
    main_subtask_usb_extra_device();
}