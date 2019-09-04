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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ethtool_regs {int len; scalar_t__ version; } ;
struct cas {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cas_read_regs (struct cas*,void*,int) ; 
 struct cas* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void cas_get_regs(struct net_device *dev, struct ethtool_regs *regs,
			     void *p)
{
	struct cas *cp = netdev_priv(dev);
	regs->version = 0;
	/* cas_read_regs handles locks (cp->lock).  */
	cas_read_regs(cp, p, regs->len / sizeof(u32));
}