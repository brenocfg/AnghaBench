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
struct ethtool_regs {scalar_t__ len; int /*<<< orphan*/  version; } ;
struct cp_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 scalar_t__ CP_REGS_SIZE ; 
 int /*<<< orphan*/  CP_REGS_VER ; 
 int /*<<< orphan*/  memcpy_fromio (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct cp_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cp_get_regs(struct net_device *dev, struct ethtool_regs *regs,
		        void *p)
{
	struct cp_private *cp = netdev_priv(dev);
	unsigned long flags;

	if (regs->len < CP_REGS_SIZE)
		return /* -EINVAL */;

	regs->version = CP_REGS_VER;

	spin_lock_irqsave(&cp->lock, flags);
	memcpy_fromio(p, cp->regs, CP_REGS_SIZE);
	spin_unlock_irqrestore(&cp->lock, flags);
}