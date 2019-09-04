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
struct net_device {unsigned char operstate; } ;

/* Variables and functions */
#define  IF_OPER_DORMANT 129 
 unsigned char IF_OPER_UNKNOWN ; 
#define  IF_OPER_UP 128 
 int /*<<< orphan*/  dev_base_lock ; 
 int /*<<< orphan*/  netdev_state_change (struct net_device*) ; 
 int /*<<< orphan*/  netif_dormant (struct net_device*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_operstate(struct net_device *dev, unsigned char transition)
{
	unsigned char operstate = dev->operstate;

	switch (transition) {
	case IF_OPER_UP:
		if ((operstate == IF_OPER_DORMANT ||
		     operstate == IF_OPER_UNKNOWN) &&
		    !netif_dormant(dev))
			operstate = IF_OPER_UP;
		break;

	case IF_OPER_DORMANT:
		if (operstate == IF_OPER_UP ||
		    operstate == IF_OPER_UNKNOWN)
			operstate = IF_OPER_DORMANT;
		break;
	}

	if (dev->operstate != operstate) {
		write_lock_bh(&dev_base_lock);
		dev->operstate = operstate;
		write_unlock_bh(&dev_base_lock);
		netdev_state_change(dev);
	}
}