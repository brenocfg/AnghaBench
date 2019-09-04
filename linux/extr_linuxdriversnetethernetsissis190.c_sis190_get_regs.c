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
struct sis190_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  mmio_addr; } ;
struct net_device {int dummy; } ;
struct ethtool_regs {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy_fromio (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sis190_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sis190_get_regs(struct net_device *dev, struct ethtool_regs *regs,
			    void *p)
{
	struct sis190_private *tp = netdev_priv(dev);
	unsigned long flags;

	spin_lock_irqsave(&tp->lock, flags);
	memcpy_fromio(p, tp->mmio_addr, regs->len);
	spin_unlock_irqrestore(&tp->lock, flags);
}