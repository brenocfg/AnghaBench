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
 int TPACPI_LED_MAX ; 
 int /*<<< orphan*/  tpacpi_led_set (int,int) ; 

__attribute__((used)) static void mute_led_exit(void)
{
	int i;

	for (i = 0; i < TPACPI_LED_MAX; i++)
		tpacpi_led_set(i, false);
}