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
 int /*<<< orphan*/  E2P_CMD ; 
 int E2P_CMD_EPC_BUSY_ ; 
 int E2P_CMD_EPC_TIMEOUT_ ; 
 int EIO ; 
 scalar_t__ HZ ; 
 unsigned long jiffies ; 
 int lan78xx_read_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  time_after (unsigned long,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int lan78xx_wait_eeprom(struct lan78xx_net *dev)
{
	unsigned long start_time = jiffies;
	u32 val;
	int ret;

	do {
		ret = lan78xx_read_reg(dev, E2P_CMD, &val);
		if (unlikely(ret < 0))
			return -EIO;

		if (!(val & E2P_CMD_EPC_BUSY_) ||
		    (val & E2P_CMD_EPC_TIMEOUT_))
			break;
		usleep_range(40, 100);
	} while (!time_after(jiffies, start_time + HZ));

	if (val & (E2P_CMD_EPC_TIMEOUT_ | E2P_CMD_EPC_BUSY_)) {
		netdev_warn(dev->net, "EEPROM read operation timeout");
		return -EIO;
	}

	return 0;
}