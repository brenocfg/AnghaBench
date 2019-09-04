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
struct orinoco_private {scalar_t__ open; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int __orinoco_down (struct orinoco_private*) ; 
 struct orinoco_private* ndev_priv (struct net_device*) ; 
 int /*<<< orphan*/  orinoco_lock_irq (struct orinoco_private*) ; 
 int /*<<< orphan*/  orinoco_unlock_irq (struct orinoco_private*) ; 

int orinoco_stop(struct net_device *dev)
{
	struct orinoco_private *priv = ndev_priv(dev);
	int err = 0;

	/* We mustn't use orinoco_lock() here, because we need to be
	   able to close the interface even if hw_unavailable is set
	   (e.g. as we're released after a PC Card removal) */
	orinoco_lock_irq(priv);

	priv->open = 0;

	err = __orinoco_down(priv);

	orinoco_unlock_irq(priv);

	return err;
}