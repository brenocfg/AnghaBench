#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  dev; } ;
struct TYPE_17__ {TYPE_9__ led; } ;
struct TYPE_16__ {TYPE_9__ led; } ;
struct TYPE_15__ {TYPE_9__ led; } ;
struct TYPE_14__ {TYPE_9__ led; } ;
struct TYPE_13__ {TYPE_9__ led; } ;
struct TYPE_12__ {TYPE_9__ led; } ;
struct TYPE_11__ {TYPE_9__ led; } ;
struct TYPE_10__ {TYPE_9__ led; } ;
struct asus_laptop {int /*<<< orphan*/ * led_workqueue; TYPE_8__ kled; TYPE_7__ gled; TYPE_6__ rled; TYPE_5__ pled; TYPE_4__ tled; TYPE_3__ mled; TYPE_2__ bled; TYPE_1__ wled; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_9__*) ; 

__attribute__((used)) static void asus_led_exit(struct asus_laptop *asus)
{
	if (!IS_ERR_OR_NULL(asus->wled.led.dev))
		led_classdev_unregister(&asus->wled.led);
	if (!IS_ERR_OR_NULL(asus->bled.led.dev))
		led_classdev_unregister(&asus->bled.led);
	if (!IS_ERR_OR_NULL(asus->mled.led.dev))
		led_classdev_unregister(&asus->mled.led);
	if (!IS_ERR_OR_NULL(asus->tled.led.dev))
		led_classdev_unregister(&asus->tled.led);
	if (!IS_ERR_OR_NULL(asus->pled.led.dev))
		led_classdev_unregister(&asus->pled.led);
	if (!IS_ERR_OR_NULL(asus->rled.led.dev))
		led_classdev_unregister(&asus->rled.led);
	if (!IS_ERR_OR_NULL(asus->gled.led.dev))
		led_classdev_unregister(&asus->gled.led);
	if (!IS_ERR_OR_NULL(asus->kled.led.dev))
		led_classdev_unregister(&asus->kled.led);
	if (asus->led_workqueue) {
		destroy_workqueue(asus->led_workqueue);
		asus->led_workqueue = NULL;
	}
}