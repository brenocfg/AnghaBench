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
struct vsc8531_private {int /*<<< orphan*/  led_0_mode; int /*<<< orphan*/  led_1_mode; int /*<<< orphan*/  rate_magic; } ;
struct phy_device {int /*<<< orphan*/  interface; struct vsc8531_private* priv; } ;

/* Variables and functions */
 int genphy_config_init (struct phy_device*) ; 
 int vsc85xx_default_config (struct phy_device*) ; 
 int vsc85xx_edge_rate_cntl_set (struct phy_device*,int /*<<< orphan*/ ) ; 
 int vsc85xx_led_cntl_set (struct phy_device*,int,int /*<<< orphan*/ ) ; 
 int vsc85xx_mac_if_set (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vsc85xx_config_init(struct phy_device *phydev)
{
	int rc;
	struct vsc8531_private *vsc8531 = phydev->priv;

	rc = vsc85xx_default_config(phydev);
	if (rc)
		return rc;

	rc = vsc85xx_mac_if_set(phydev, phydev->interface);
	if (rc)
		return rc;

	rc = vsc85xx_edge_rate_cntl_set(phydev, vsc8531->rate_magic);
	if (rc)
		return rc;

	rc = vsc85xx_led_cntl_set(phydev, 1, vsc8531->led_1_mode);
	if (rc)
		return rc;

	rc = vsc85xx_led_cntl_set(phydev, 0, vsc8531->led_0_mode);
	if (rc)
		return rc;

	rc = genphy_config_init(phydev);

	return rc;
}