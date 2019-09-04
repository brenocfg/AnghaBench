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
struct net_local {scalar_t__ base_addr; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int XEL_MDIOCTRL_MDIOSTS_MASK ; 
 scalar_t__ XEL_MDIOCTRL_OFFSET ; 
 int jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_before_eq (unsigned long,int) ; 
 int xemaclite_readl (scalar_t__) ; 

__attribute__((used)) static int xemaclite_mdio_wait(struct net_local *lp)
{
	unsigned long end = jiffies + 2;

	/* wait for the MDIO interface to not be busy or timeout
	 * after some time.
	 */
	while (xemaclite_readl(lp->base_addr + XEL_MDIOCTRL_OFFSET) &
			XEL_MDIOCTRL_MDIOSTS_MASK) {
		if (time_before_eq(end, jiffies)) {
			WARN_ON(1);
			return -ETIMEDOUT;
		}
		msleep(1);
	}
	return 0;
}