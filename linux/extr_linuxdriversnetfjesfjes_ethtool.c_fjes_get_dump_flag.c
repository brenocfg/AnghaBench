#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  trace_size; } ;
struct fjes_hw {int /*<<< orphan*/  debug_mode; TYPE_1__ hw_info; } ;
struct fjes_adapter {struct fjes_hw hw; } ;
struct ethtool_dump {int version; int /*<<< orphan*/  flag; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 struct fjes_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int fjes_get_dump_flag(struct net_device *netdev,
			      struct ethtool_dump *dump)
{
	struct fjes_adapter *adapter = netdev_priv(netdev);
	struct fjes_hw *hw = &adapter->hw;

	dump->len = hw->hw_info.trace_size;
	dump->version = 1;
	dump->flag = hw->debug_mode;

	return 0;
}