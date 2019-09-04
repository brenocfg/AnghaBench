#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * eth_addr; } ;
struct sgiseeq_regs {TYPE_1__ rw; int /*<<< orphan*/  tstat; } ;
struct sgiseeq_private {struct sgiseeq_regs* sregs; } ;
struct net_device {int /*<<< orphan*/ * dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEQ_TCMD_RB0 ; 
 struct sgiseeq_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline void __sgiseeq_set_mac_address(struct net_device *dev)
{
	struct sgiseeq_private *sp = netdev_priv(dev);
	struct sgiseeq_regs *sregs = sp->sregs;
	int i;

	sregs->tstat = SEEQ_TCMD_RB0;
	for (i = 0; i < 6; i++)
		sregs->rw.eth_addr[i] = dev->dev_addr[i];
}