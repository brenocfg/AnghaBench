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
typedef  scalar_t__ u32 ;
struct rcar_gen3_thermal_priv {int num_tscs; int /*<<< orphan*/  lock; int /*<<< orphan*/ * tscs; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int IRQ_HANDLED ; 
 int IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  REG_GEN3_IRQSTR ; 
 scalar_t__ rcar_gen3_thermal_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_gen3_thermal_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_thermal_irq_set (struct rcar_gen3_thermal_priv*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t rcar_gen3_thermal_irq(int irq, void *data)
{
	struct rcar_gen3_thermal_priv *priv = data;
	u32 status;
	int i, ret = IRQ_HANDLED;

	spin_lock(&priv->lock);
	for (i = 0; i < priv->num_tscs; i++) {
		status = rcar_gen3_thermal_read(priv->tscs[i], REG_GEN3_IRQSTR);
		rcar_gen3_thermal_write(priv->tscs[i], REG_GEN3_IRQSTR, 0);
		if (status)
			ret = IRQ_WAKE_THREAD;
	}

	if (ret == IRQ_WAKE_THREAD)
		rcar_thermal_irq_set(priv, false);

	spin_unlock(&priv->lock);

	return ret;
}