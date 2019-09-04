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
struct TYPE_2__ {int /*<<< orphan*/  txqueue_timer; int /*<<< orphan*/  rxqueue_timer; int /*<<< orphan*/  rx_intsup; int /*<<< orphan*/  tx_intsup; } ;
struct velocity_info {TYPE_1__ options; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {void* tx_coalesce_usecs; void* rx_coalesce_usecs; int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  tx_max_coalesced_frames; } ;

/* Variables and functions */
 void* get_pending_timer_val (int /*<<< orphan*/ ) ; 
 struct velocity_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int velocity_get_coalesce(struct net_device *dev,
		struct ethtool_coalesce *ecmd)
{
	struct velocity_info *vptr = netdev_priv(dev);

	ecmd->tx_max_coalesced_frames = vptr->options.tx_intsup;
	ecmd->rx_max_coalesced_frames = vptr->options.rx_intsup;

	ecmd->rx_coalesce_usecs = get_pending_timer_val(vptr->options.rxqueue_timer);
	ecmd->tx_coalesce_usecs = get_pending_timer_val(vptr->options.txqueue_timer);

	return 0;
}