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
typedef  int u32 ;
struct rcar_gen3_thermal_priv {unsigned int num_tscs; int /*<<< orphan*/ * tscs; } ;

/* Variables and functions */
 int IRQ_TEMP2 ; 
 int IRQ_TEMPD1 ; 
 int /*<<< orphan*/  REG_GEN3_IRQMSK ; 
 int /*<<< orphan*/  rcar_gen3_thermal_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rcar_thermal_irq_set(struct rcar_gen3_thermal_priv *priv, bool on)
{
	unsigned int i;
	u32 val = on ? IRQ_TEMPD1 | IRQ_TEMP2 : 0;

	for (i = 0; i < priv->num_tscs; i++)
		rcar_gen3_thermal_write(priv->tscs[i], REG_GEN3_IRQMSK, val);
}