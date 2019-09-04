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

/* Variables and functions */
 int /*<<< orphan*/  CPU_GEN ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mdelay (int) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int rtl92e_readl (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static bool _rtl92e_wait_for_fw(struct net_device *dev, u32 mask, u32 timeout)
{
	unsigned long deadline = jiffies + msecs_to_jiffies(timeout);

	while (time_before(jiffies, deadline)) {
		if (rtl92e_readl(dev, CPU_GEN) & mask)
			return true;
		mdelay(2);
	}
	return false;
}