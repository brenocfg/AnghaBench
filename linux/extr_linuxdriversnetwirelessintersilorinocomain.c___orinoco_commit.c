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
struct orinoco_private {scalar_t__ tkip_cm_active; struct net_device* ndev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __orinoco_set_multicast_list (struct net_device*) ; 
 int orinoco_hw_program_rids (struct orinoco_private*) ; 

__attribute__((used)) static int __orinoco_commit(struct orinoco_private *priv)
{
	struct net_device *dev = priv->ndev;
	int err = 0;

	/* If we've called commit, we are reconfiguring or bringing the
	 * interface up. Maintaining countermeasures across this would
	 * be confusing, so note that we've disabled them. The port will
	 * be enabled later in orinoco_commit or __orinoco_up. */
	priv->tkip_cm_active = 0;

	err = orinoco_hw_program_rids(priv);

	/* FIXME: what about netif_tx_lock */
	(void) __orinoco_set_multicast_list(dev);

	return err;
}