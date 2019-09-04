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
struct rcar_gen3_thermal_priv {int num_tscs; int /*<<< orphan*/  lock; TYPE_1__** tscs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  THERMAL_EVENT_UNSPECIFIED ; 
 int /*<<< orphan*/  rcar_thermal_irq_set (struct rcar_gen3_thermal_priv*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  thermal_zone_device_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rcar_gen3_thermal_irq_thread(int irq, void *data)
{
	struct rcar_gen3_thermal_priv *priv = data;
	unsigned long flags;
	int i;

	for (i = 0; i < priv->num_tscs; i++)
		thermal_zone_device_update(priv->tscs[i]->zone,
					   THERMAL_EVENT_UNSPECIFIED);

	spin_lock_irqsave(&priv->lock, flags);
	rcar_thermal_irq_set(priv, true);
	spin_unlock_irqrestore(&priv->lock, flags);

	return IRQ_HANDLED;
}