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
struct vsc8531_private {int rate_magic; int led_0_mode; int led_1_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct phy_device {struct vsc8531_private* priv; TYPE_1__ mdio; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VSC8531_LINK_1000_ACTIVITY ; 
 int /*<<< orphan*/  VSC8531_LINK_100_ACTIVITY ; 
 struct vsc8531_private* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int vsc85xx_dt_led_mode_get (struct phy_device*,char*,int /*<<< orphan*/ ) ; 
 int vsc85xx_edge_rate_magic_get (struct phy_device*) ; 

__attribute__((used)) static int vsc85xx_probe(struct phy_device *phydev)
{
	struct vsc8531_private *vsc8531;
	int rate_magic;
	int led_mode;

	rate_magic = vsc85xx_edge_rate_magic_get(phydev);
	if (rate_magic < 0)
		return rate_magic;

	vsc8531 = devm_kzalloc(&phydev->mdio.dev, sizeof(*vsc8531), GFP_KERNEL);
	if (!vsc8531)
		return -ENOMEM;

	phydev->priv = vsc8531;

	vsc8531->rate_magic = rate_magic;

	/* LED[0] and LED[1] mode */
	led_mode = vsc85xx_dt_led_mode_get(phydev, "vsc8531,led-0-mode",
					   VSC8531_LINK_1000_ACTIVITY);
	if (led_mode < 0)
		return led_mode;
	vsc8531->led_0_mode = led_mode;

	led_mode = vsc85xx_dt_led_mode_get(phydev, "vsc8531,led-1-mode",
					   VSC8531_LINK_100_ACTIVITY);
	if (led_mode < 0)
		return led_mode;
	vsc8531->led_1_mode = led_mode;

	return 0;
}