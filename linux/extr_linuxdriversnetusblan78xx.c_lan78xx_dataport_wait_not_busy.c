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
struct lan78xx_net {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_SEL ; 
 int DP_SEL_DPRDY_ ; 
 int EIO ; 
 int lan78xx_read_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int lan78xx_dataport_wait_not_busy(struct lan78xx_net *dev)
{
	int i, ret;

	for (i = 0; i < 100; i++) {
		u32 dp_sel;

		ret = lan78xx_read_reg(dev, DP_SEL, &dp_sel);
		if (unlikely(ret < 0))
			return -EIO;

		if (dp_sel & DP_SEL_DPRDY_)
			return 0;

		usleep_range(40, 100);
	}

	netdev_warn(dev->net, "lan78xx_dataport_wait_not_busy timed out");

	return -EIO;
}