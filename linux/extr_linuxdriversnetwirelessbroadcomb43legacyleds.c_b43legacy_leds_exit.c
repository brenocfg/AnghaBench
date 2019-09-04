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
struct b43legacy_wldev {int /*<<< orphan*/  led_radio; int /*<<< orphan*/  led_assoc; int /*<<< orphan*/  led_rx; int /*<<< orphan*/  led_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43legacy_unregister_led (int /*<<< orphan*/ *) ; 

void b43legacy_leds_exit(struct b43legacy_wldev *dev)
{
	b43legacy_unregister_led(&dev->led_tx);
	b43legacy_unregister_led(&dev->led_rx);
	b43legacy_unregister_led(&dev->led_assoc);
	b43legacy_unregister_led(&dev->led_radio);
}