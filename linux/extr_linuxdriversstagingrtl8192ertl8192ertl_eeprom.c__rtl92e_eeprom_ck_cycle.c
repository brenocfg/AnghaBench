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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROM_CK_BIT ; 
 int /*<<< orphan*/  _rtl92e_gpio_write_bit (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _rtl92e_eeprom_ck_cycle(struct net_device *dev)
{
	_rtl92e_gpio_write_bit(dev, EPROM_CK_BIT, 1);
	_rtl92e_gpio_write_bit(dev, EPROM_CK_BIT, 0);
}