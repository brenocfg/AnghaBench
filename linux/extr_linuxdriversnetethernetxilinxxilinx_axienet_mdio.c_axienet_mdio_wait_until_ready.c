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
struct axienet_local {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  XAE_MDIO_MCR_OFFSET ; 
 int XAE_MDIO_MCR_READY_MASK ; 
 int axienet_ior (struct axienet_local*,int /*<<< orphan*/ ) ; 
 int jiffies ; 
 scalar_t__ time_before_eq (unsigned long,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int axienet_mdio_wait_until_ready(struct axienet_local *lp)
{
	unsigned long end = jiffies + 2;
	while (!(axienet_ior(lp, XAE_MDIO_MCR_OFFSET) &
		 XAE_MDIO_MCR_READY_MASK)) {
		if (time_before_eq(end, jiffies)) {
			WARN_ON(1);
			return -ETIMEDOUT;
		}
		udelay(1);
	}
	return 0;
}