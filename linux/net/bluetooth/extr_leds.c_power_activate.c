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
struct led_classdev {int /*<<< orphan*/  trigger; } ;
struct hci_basic_led_trigger {TYPE_1__* hdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_UP ; 
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LED_OFF ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hci_basic_led_trigger* to_hci_basic_led_trigger (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int power_activate(struct led_classdev *led_cdev)
{
	struct hci_basic_led_trigger *htrig;
	bool powered;

	htrig = to_hci_basic_led_trigger(led_cdev->trigger);
	powered = test_bit(HCI_UP, &htrig->hdev->flags);

	led_trigger_event(led_cdev->trigger, powered ? LED_FULL : LED_OFF);

	return 0;
}