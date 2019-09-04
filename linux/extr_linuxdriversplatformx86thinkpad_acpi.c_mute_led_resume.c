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
struct tp_led_table {scalar_t__ state; } ;

/* Variables and functions */
 int TPACPI_LED_MAX ; 
 struct tp_led_table* led_tables ; 
 int /*<<< orphan*/  mute_led_on_off (struct tp_led_table*,scalar_t__) ; 

__attribute__((used)) static void mute_led_resume(void)
{
	int i;

	for (i = 0; i < TPACPI_LED_MAX; i++) {
		struct tp_led_table *t = &led_tables[i];
		if (t->state >= 0)
			mute_led_on_off(t, t->state);
	}
}