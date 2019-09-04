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
struct sdw_cdns {scalar_t__ registers; } ;

/* Variables and functions */
 int EAGAIN ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int cdns_clear_bit(struct sdw_cdns *cdns, int offset, u32 value)
{
	int timeout = 10;
	u32 reg_read;

	writel(value, cdns->registers + offset);

	/* Wait for bit to be self cleared */
	do {
		reg_read = readl(cdns->registers + offset);
		if ((reg_read & value) == 0)
			return 0;

		timeout--;
		udelay(50);
	} while (timeout != 0);

	return -EAGAIN;
}