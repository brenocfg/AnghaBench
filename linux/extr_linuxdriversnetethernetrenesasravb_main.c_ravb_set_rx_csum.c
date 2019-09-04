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
struct ravb_private {int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECMR ; 
 int /*<<< orphan*/  ECMR_RCSC ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ravb_modify (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ravb_rcv_snd_disable (struct net_device*) ; 
 int /*<<< orphan*/  ravb_rcv_snd_enable (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ravb_set_rx_csum(struct net_device *ndev, bool enable)
{
	struct ravb_private *priv = netdev_priv(ndev);
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);

	/* Disable TX and RX */
	ravb_rcv_snd_disable(ndev);

	/* Modify RX Checksum setting */
	ravb_modify(ndev, ECMR, ECMR_RCSC, enable ? ECMR_RCSC : 0);

	/* Enable TX and RX */
	ravb_rcv_snd_enable(ndev);

	spin_unlock_irqrestore(&priv->lock, flags);
}