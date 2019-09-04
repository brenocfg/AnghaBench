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
struct b43_wldev {TYPE_2__* wl; } ;
typedef  enum b43_led_behaviour { ____Placeholder_b43_led_behaviour } b43_led_behaviour ;
struct TYPE_3__ {int /*<<< orphan*/  work; } ;
struct TYPE_4__ {TYPE_1__ leds; } ;

/* Variables and functions */
 unsigned int B43_MAX_NR_LEDS ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_led_get_sprominfo (struct b43_wldev*,unsigned int,int*,int*) ; 
 int /*<<< orphan*/  b43_leds_work ; 
 int /*<<< orphan*/  b43_map_led (struct b43_wldev*,unsigned int,int,int) ; 

void b43_leds_register(struct b43_wldev *dev)
{
	unsigned int i;
	enum b43_led_behaviour behaviour;
	bool activelow;

	INIT_WORK(&dev->wl->leds.work, b43_leds_work);

	/* Register the LEDs to the LED subsystem. */
	for (i = 0; i < B43_MAX_NR_LEDS; i++) {
		b43_led_get_sprominfo(dev, i, &behaviour, &activelow);
		b43_map_led(dev, i, behaviour, activelow);
	}
}