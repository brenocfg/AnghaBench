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
struct net_device {int dummy; } ;
struct bigmac {int sw_bmsr; int /*<<< orphan*/  lock; int /*<<< orphan*/  tregs; } ;

/* Variables and functions */
 int BMSR_LSTATUS ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int bigmac_tcvr_read (struct bigmac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bigmac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 bigmac_get_link(struct net_device *dev)
{
	struct bigmac *bp = netdev_priv(dev);

	spin_lock_irq(&bp->lock);
	bp->sw_bmsr = bigmac_tcvr_read(bp, bp->tregs, MII_BMSR);
	spin_unlock_irq(&bp->lock);

	return (bp->sw_bmsr & BMSR_LSTATUS);
}