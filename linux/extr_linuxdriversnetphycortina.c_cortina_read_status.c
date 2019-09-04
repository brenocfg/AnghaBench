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
struct phy_device {int link; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int /*<<< orphan*/  VILLA_GLOBAL_GPIO_1_INTS ; 
 int cortina_read_reg (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cortina_read_status(struct phy_device *phydev)
{
	int gpio_int_status, ret = 0;

	gpio_int_status = cortina_read_reg(phydev, VILLA_GLOBAL_GPIO_1_INTS);
	if (gpio_int_status < 0) {
		ret = gpio_int_status;
		goto err;
	}

	if (gpio_int_status & 0x8) {
		/* up when edc_convergedS set */
		phydev->speed = SPEED_10000;
		phydev->duplex = DUPLEX_FULL;
		phydev->link = 1;
	} else {
		phydev->link = 0;
	}

err:
	return ret;
}