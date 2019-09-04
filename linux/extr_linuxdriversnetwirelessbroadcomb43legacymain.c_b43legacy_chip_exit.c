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
struct b43legacy_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43legacy_gpio_cleanup (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_radio_turn_off (struct b43legacy_wldev*,int) ; 

__attribute__((used)) static void b43legacy_chip_exit(struct b43legacy_wldev *dev)
{
	b43legacy_radio_turn_off(dev, 1);
	b43legacy_gpio_cleanup(dev);
	/* firmware is released later */
}