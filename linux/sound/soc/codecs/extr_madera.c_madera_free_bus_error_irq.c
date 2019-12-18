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
struct madera {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * madera_dsp_bus_error_irqs ; 
 int /*<<< orphan*/  madera_free_irq (struct madera*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void madera_free_bus_error_irq(struct madera_priv *priv, int dsp_num)
{
	struct madera *madera = priv->madera;

	madera_free_irq(madera,
			madera_dsp_bus_error_irqs[dsp_num],
			&priv->adsp[dsp_num]);
}