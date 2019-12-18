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
struct madera_priv {int /*<<< orphan*/ * adsp; struct madera* madera; } ;
struct madera {int /*<<< orphan*/  dev; } ;
struct cs47l92 {struct madera_priv core; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int wm_adsp_compr_handle_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t cs47l92_adsp2_irq(int irq, void *data)
{
	struct cs47l92 *cs47l92 = data;
	struct madera_priv *priv = &cs47l92->core;
	struct madera *madera = priv->madera;
	int ret;

	ret = wm_adsp_compr_handle_irq(&priv->adsp[0]);
	if (ret == -ENODEV) {
		dev_err(madera->dev, "Spurious compressed data IRQ\n");
		return IRQ_NONE;
	}

	return IRQ_HANDLED;
}