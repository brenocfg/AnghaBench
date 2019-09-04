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
 int /*<<< orphan*/  i8042_command (char*,int) ; 

__attribute__((used)) static void touchpad_led_off(void)
{
	int command = 0x97;
	char data = 2;
	i8042_command(&data, command | 1 << 12);
}