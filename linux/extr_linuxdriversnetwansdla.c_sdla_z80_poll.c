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
struct net_device {scalar_t__ mem_start; } ;

/* Variables and functions */
 int SDLA_ADDR_MASK ; 
 int /*<<< orphan*/  SDLA_WINDOW (struct net_device*,int) ; 
 int jiffies ; 
 scalar_t__ time_before (int,unsigned long) ; 

__attribute__((used)) static int sdla_z80_poll(struct net_device *dev, int z80_addr, int jiffs, char resp1, char resp2)
{
	unsigned long start, done, now;
	char          resp, *temp;

	start = now = jiffies;
	done = jiffies + jiffs;

	temp = (void *)dev->mem_start;
	temp += z80_addr & SDLA_ADDR_MASK;
	
	resp = ~resp1;
	while (time_before(jiffies, done) && (resp != resp1) && (!resp2 || (resp != resp2)))
	{
		if (jiffies != now)
		{
			SDLA_WINDOW(dev, z80_addr);
			now = jiffies;
			resp = *temp;
		}
	}
	return time_before(jiffies, done) ? jiffies - start : -1;
}