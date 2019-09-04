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
typedef  int u8 ;
struct mxc_w1_device {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ MXC_W1_CONTROL ; 
 int MXC_W1_CONTROL_RDST ; 
 int MXC_W1_CONTROL_WR (int) ; 
 unsigned long jiffies ; 
 int readb (scalar_t__) ; 
 scalar_t__ time_is_after_jiffies (unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 unsigned long usecs_to_jiffies (int) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static u8 mxc_w1_ds2_touch_bit(void *data, u8 bit)
{
	struct mxc_w1_device *dev = data;
	unsigned long timeout;

	writeb(MXC_W1_CONTROL_WR(bit), dev->regs + MXC_W1_CONTROL);

	/* Wait for read/write bit (60us, Max 120us), use 200us for sure */
	timeout = jiffies + usecs_to_jiffies(200);

	udelay(60);

	do {
		u8 ctrl = readb(dev->regs + MXC_W1_CONTROL);

		/* RDST bit is valid after the WR1/RD bit is self-cleared */
		if (!(ctrl & MXC_W1_CONTROL_WR(bit)))
			return !!(ctrl & MXC_W1_CONTROL_RDST);
	} while (time_is_after_jiffies(timeout));

	return 0;
}