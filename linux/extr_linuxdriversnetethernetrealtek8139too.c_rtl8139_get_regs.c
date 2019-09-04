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
struct rtl8139_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  mmio_addr; } ;
struct net_device {int dummy; } ;
struct ethtool_regs {int /*<<< orphan*/  len; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTL_REGS_VER ; 
 int /*<<< orphan*/  memcpy_fromio (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl8139_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ use_io ; 

__attribute__((used)) static void rtl8139_get_regs(struct net_device *dev, struct ethtool_regs *regs, void *regbuf)
{
	struct rtl8139_private *tp;

	/* TODO: we are too slack to do reg dumping for pio, for now */
	if (use_io)
		return;
	tp = netdev_priv(dev);

	regs->version = RTL_REGS_VER;

	spin_lock_irq(&tp->lock);
	memcpy_fromio(regbuf, tp->mmio_addr, regs->len);
	spin_unlock_irq(&tp->lock);
}