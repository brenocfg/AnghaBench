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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct eeepc_laptop {scalar_t__ led_workqueue; TYPE_1__ tpd_led; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_1__*) ; 

__attribute__((used)) static void eeepc_led_exit(struct eeepc_laptop *eeepc)
{
	if (!IS_ERR_OR_NULL(eeepc->tpd_led.dev))
		led_classdev_unregister(&eeepc->tpd_led);
	if (eeepc->led_workqueue)
		destroy_workqueue(eeepc->led_workqueue);
}