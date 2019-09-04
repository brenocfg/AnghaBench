#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int fan_ctrl_status_undef; } ;

/* Variables and functions */
 int fan_control_initial_status ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 TYPE_1__ tp_features ; 

__attribute__((used)) static void fan_quirk1_setup(void)
{
	if (fan_control_initial_status == 0x07) {
		pr_notice("fan_init: initial fan status is unknown, assuming it is in auto mode\n");
		tp_features.fan_ctrl_status_undef = 1;
	}
}