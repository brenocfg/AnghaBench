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
typedef  unsigned int u32 ;
struct sunxi_rtc_dev {scalar_t__ base; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (unsigned int) ; 
 unsigned int readl (scalar_t__) ; 
 scalar_t__ time_before (unsigned long,unsigned long const) ; 

__attribute__((used)) static int sunxi_rtc_wait(struct sunxi_rtc_dev *chip, int offset,
			  unsigned int mask, unsigned int ms_timeout)
{
	const unsigned long timeout = jiffies + msecs_to_jiffies(ms_timeout);
	u32 reg;

	do {
		reg = readl(chip->base + offset);
		reg &= mask;

		if (reg == mask)
			return 0;

	} while (time_before(jiffies, timeout));

	return -ETIMEDOUT;
}