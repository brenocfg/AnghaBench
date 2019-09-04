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
struct net_device {int dummy; } ;
struct emac_priv {int /*<<< orphan*/  napi; int /*<<< orphan*/  ndev; int /*<<< orphan*/  isr_count; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  emac_int_disable (struct emac_priv*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct emac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t emac_irq(int irq, void *dev_id)
{
	struct net_device *ndev = (struct net_device *)dev_id;
	struct emac_priv *priv = netdev_priv(ndev);

	++priv->isr_count;
	if (likely(netif_running(priv->ndev))) {
		emac_int_disable(priv);
		napi_schedule(&priv->napi);
	} else {
		/* we are closing down, so dont process anything */
	}
	return IRQ_HANDLED;
}