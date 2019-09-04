#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* name; int max_brightness; int /*<<< orphan*/  brightness_get; int /*<<< orphan*/  brightness_set; } ;
struct eeepc_laptop {int /*<<< orphan*/  led_workqueue; TYPE_2__ tpd_led; TYPE_1__* platform_device; int /*<<< orphan*/  tpd_led_work; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_ASL_TPD ; 
 int /*<<< orphan*/  ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_acpi (struct eeepc_laptop*,int /*<<< orphan*/ ) ; 
 int led_classdev_register (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  tpd_led_get ; 
 int /*<<< orphan*/  tpd_led_set ; 
 int /*<<< orphan*/  tpd_led_update ; 

__attribute__((used)) static int eeepc_led_init(struct eeepc_laptop *eeepc)
{
	int rv;

	if (get_acpi(eeepc, CM_ASL_TPD) == -ENODEV)
		return 0;

	eeepc->led_workqueue = create_singlethread_workqueue("led_workqueue");
	if (!eeepc->led_workqueue)
		return -ENOMEM;
	INIT_WORK(&eeepc->tpd_led_work, tpd_led_update);

	eeepc->tpd_led.name = "eeepc::touchpad";
	eeepc->tpd_led.brightness_set = tpd_led_set;
	if (get_acpi(eeepc, CM_ASL_TPD) >= 0) /* if method is available */
		eeepc->tpd_led.brightness_get = tpd_led_get;
	eeepc->tpd_led.max_brightness = 1;

	rv = led_classdev_register(&eeepc->platform_device->dev,
				   &eeepc->tpd_led);
	if (rv) {
		destroy_workqueue(eeepc->led_workqueue);
		return rv;
	}

	return 0;
}