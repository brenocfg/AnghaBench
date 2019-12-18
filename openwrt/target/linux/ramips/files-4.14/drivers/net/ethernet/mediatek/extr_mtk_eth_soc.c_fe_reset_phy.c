#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gpio_desc {int dummy; } ;
struct fe_priv {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 struct gpio_desc* devm_gpiod_get_optional (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (struct gpio_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void fe_reset_phy(struct fe_priv *priv)
{
	int err, msec = 30;
	struct gpio_desc *phy_reset;

	phy_reset = devm_gpiod_get_optional(priv->dev, "phy-reset",
					    GPIOD_OUT_HIGH);
	if (!phy_reset)
		return;

	if (IS_ERR(phy_reset)) {
		dev_err(priv->dev, "Error acquiring reset gpio pins: %ld\n",
			PTR_ERR(phy_reset));
		return;
	}

	err = of_property_read_u32(priv->dev->of_node, "phy-reset-duration",
				   &msec);
	if (!err && msec > 1000)
		msec = 30;

	if (msec > 20)
		msleep(msec);
	else
		usleep_range(msec * 1000, msec * 1000 + 1000);

	gpiod_set_value(phy_reset, 0);
}