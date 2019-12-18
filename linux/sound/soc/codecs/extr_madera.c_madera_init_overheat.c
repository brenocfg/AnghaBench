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
struct madera_priv {struct madera* madera; } ;
struct madera {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MADERA_IRQ_SPK_OVERHEAT ; 
 int /*<<< orphan*/  MADERA_IRQ_SPK_OVERHEAT_WARN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int madera_request_irq (struct madera*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct madera*) ; 
 int /*<<< orphan*/  madera_thermal_warn ; 

int madera_init_overheat(struct madera_priv *priv)
{
	struct madera *madera = priv->madera;
	struct device *dev = madera->dev;
	int ret;

	ret = madera_request_irq(madera, MADERA_IRQ_SPK_OVERHEAT_WARN,
				 "Thermal warning", madera_thermal_warn,
				 madera);
	if (ret)
		dev_err(dev, "Failed to get thermal warning IRQ: %d\n", ret);

	ret = madera_request_irq(madera, MADERA_IRQ_SPK_OVERHEAT,
				 "Thermal shutdown", madera_thermal_warn,
				 madera);
	if (ret)
		dev_err(dev, "Failed to get thermal shutdown IRQ: %d\n", ret);

	return 0;
}