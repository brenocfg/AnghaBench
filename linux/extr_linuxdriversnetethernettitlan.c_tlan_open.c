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
struct tlan_priv {int /*<<< orphan*/  tlan_rev; int /*<<< orphan*/  media_timer; int /*<<< orphan*/  timer; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  TLAN_DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLAN_DEBUG_GNRL ; 
 int /*<<< orphan*/  TLAN_DEF_REVISION ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct tlan_priv* netdev_priv (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlan_dio_read8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlan_handle_interrupt ; 
 int /*<<< orphan*/ * tlan_phy_monitor ; 
 int /*<<< orphan*/  tlan_start (struct net_device*) ; 

__attribute__((used)) static int tlan_open(struct net_device *dev)
{
	struct tlan_priv	*priv = netdev_priv(dev);
	int		err;

	priv->tlan_rev = tlan_dio_read8(dev->base_addr, TLAN_DEF_REVISION);
	err = request_irq(dev->irq, tlan_handle_interrupt, IRQF_SHARED,
			  dev->name, dev);

	if (err) {
		netdev_err(dev, "Cannot open because IRQ %d is already in use\n",
			   dev->irq);
		return err;
	}

	timer_setup(&priv->timer, NULL, 0);
	timer_setup(&priv->media_timer, tlan_phy_monitor, 0);

	tlan_start(dev);

	TLAN_DBG(TLAN_DEBUG_GNRL, "%s: Opened.  TLAN Chip Rev: %x\n",
		 dev->name, priv->tlan_rev);

	return 0;

}