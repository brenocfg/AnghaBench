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
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * madera_dsp_bus_error_irqs ; 
 int madera_request_irq (struct madera*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int madera_init_bus_error_irq(struct madera_priv *priv, int dsp_num,
			      irq_handler_t handler)
{
	struct madera *madera = priv->madera;
	int ret;

	ret = madera_request_irq(madera,
				 madera_dsp_bus_error_irqs[dsp_num],
				 "ADSP2 bus error",
				 handler,
				 &priv->adsp[dsp_num]);
	if (ret)
		dev_err(madera->dev,
			"Failed to request DSP Lock region IRQ: %d\n", ret);

	return ret;
}