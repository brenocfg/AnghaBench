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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct phy_device {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int LED_0_MODE_SEL_MASK ; 
 int LED_1_MODE_SEL_MASK ; 
 int LED_1_MODE_SEL_POS ; 
 int /*<<< orphan*/  MSCC_PHY_LED_MODE_SEL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vsc85xx_led_cntl_set(struct phy_device *phydev,
				u8 led_num,
				u8 mode)
{
	int rc;
	u16 reg_val;

	mutex_lock(&phydev->lock);
	reg_val = phy_read(phydev, MSCC_PHY_LED_MODE_SEL);
	if (led_num) {
		reg_val &= ~LED_1_MODE_SEL_MASK;
		reg_val |= (((u16)mode << LED_1_MODE_SEL_POS) &
			    LED_1_MODE_SEL_MASK);
	} else {
		reg_val &= ~LED_0_MODE_SEL_MASK;
		reg_val |= ((u16)mode & LED_0_MODE_SEL_MASK);
	}
	rc = phy_write(phydev, MSCC_PHY_LED_MODE_SEL, reg_val);
	mutex_unlock(&phydev->lock);

	return rc;
}