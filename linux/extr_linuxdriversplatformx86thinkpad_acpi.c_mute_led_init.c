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
struct tp_led_table {int /*<<< orphan*/  state; int /*<<< orphan*/  name; } ;
struct ibm_init_struct {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENODEV ; 
 int TPACPI_LED_MAX ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hkey_handle ; 
 struct tp_led_table* led_tables ; 
 int /*<<< orphan*/  mute_led_on_off (struct tp_led_table*,int) ; 

__attribute__((used)) static int mute_led_init(struct ibm_init_struct *iibm)
{
	acpi_handle temp;
	int i;

	for (i = 0; i < TPACPI_LED_MAX; i++) {
		struct tp_led_table *t = &led_tables[i];
		if (ACPI_SUCCESS(acpi_get_handle(hkey_handle, t->name, &temp)))
			mute_led_on_off(t, false);
		else
			t->state = -ENODEV;
	}
	return 0;
}