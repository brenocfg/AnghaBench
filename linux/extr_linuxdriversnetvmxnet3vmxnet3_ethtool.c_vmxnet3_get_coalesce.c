#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct vmxnet3_adapter {TYPE_4__* coal_conf; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int use_adaptive_rx_coalesce; int /*<<< orphan*/  rx_coalesce_usecs; int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  tx_max_coalesced_frames; } ;
struct TYPE_6__ {int /*<<< orphan*/  rbc_rate; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx_depth; int /*<<< orphan*/  tx_comp_depth; } ;
struct TYPE_7__ {TYPE_2__ coalRbc; TYPE_1__ coalStatic; } ;
struct TYPE_8__ {int coalMode; TYPE_3__ coalPara; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  VMXNET3_COALESCE_ADAPT 131 
#define  VMXNET3_COALESCE_DISABLED 130 
#define  VMXNET3_COALESCE_RBC 129 
#define  VMXNET3_COALESCE_STATIC 128 
 int /*<<< orphan*/  VMXNET3_COAL_RBC_USECS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMXNET3_VERSION_GE_3 (struct vmxnet3_adapter*) ; 
 struct vmxnet3_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
vmxnet3_get_coalesce(struct net_device *netdev, struct ethtool_coalesce *ec)
{
	struct vmxnet3_adapter *adapter = netdev_priv(netdev);

	if (!VMXNET3_VERSION_GE_3(adapter))
		return -EOPNOTSUPP;

	switch (adapter->coal_conf->coalMode) {
	case VMXNET3_COALESCE_DISABLED:
		/* struct ethtool_coalesce is already initialized to 0 */
		break;
	case VMXNET3_COALESCE_ADAPT:
		ec->use_adaptive_rx_coalesce = true;
		break;
	case VMXNET3_COALESCE_STATIC:
		ec->tx_max_coalesced_frames =
			adapter->coal_conf->coalPara.coalStatic.tx_comp_depth;
		ec->rx_max_coalesced_frames =
			adapter->coal_conf->coalPara.coalStatic.rx_depth;
		break;
	case VMXNET3_COALESCE_RBC: {
		u32 rbc_rate;

		rbc_rate = adapter->coal_conf->coalPara.coalRbc.rbc_rate;
		ec->rx_coalesce_usecs = VMXNET3_COAL_RBC_USECS(rbc_rate);
	}
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}