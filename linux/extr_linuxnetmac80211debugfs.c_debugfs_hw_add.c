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
struct TYPE_8__ {void* keys; } ;
struct TYPE_7__ {TYPE_2__* wiphy; } ;
struct ieee80211_local {TYPE_1__* ops; TYPE_4__ debugfs; TYPE_3__ hw; } ;
struct dentry {int dummy; } ;
struct TYPE_6__ {struct dentry* debugfsdir; } ;
struct TYPE_5__ {scalar_t__ wake_tx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFS_ADD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGFS_ADD_MODE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DEBUGFS_DEVSTATS_ADD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aqm ; 
 void* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  dot11ACKFailureCount ; 
 int /*<<< orphan*/  dot11FCSErrorCount ; 
 int /*<<< orphan*/  dot11RTSFailureCount ; 
 int /*<<< orphan*/  dot11RTSSuccessCount ; 
 int /*<<< orphan*/  hwflags ; 
 int /*<<< orphan*/  misc ; 
 int /*<<< orphan*/  power ; 
 int /*<<< orphan*/  queues ; 
 int /*<<< orphan*/  rate_ctrl_alg ; 
 int /*<<< orphan*/  total_ps_buffered ; 
 int /*<<< orphan*/  user_power ; 
 int /*<<< orphan*/  wep_iv ; 

void debugfs_hw_add(struct ieee80211_local *local)
{
	struct dentry *phyd = local->hw.wiphy->debugfsdir;
	struct dentry *statsd;

	if (!phyd)
		return;

	local->debugfs.keys = debugfs_create_dir("keys", phyd);

	DEBUGFS_ADD(total_ps_buffered);
	DEBUGFS_ADD(wep_iv);
	DEBUGFS_ADD(rate_ctrl_alg);
	DEBUGFS_ADD(queues);
	DEBUGFS_ADD(misc);
#ifdef CONFIG_PM
	DEBUGFS_ADD_MODE(reset, 0200);
#endif
	DEBUGFS_ADD(hwflags);
	DEBUGFS_ADD(user_power);
	DEBUGFS_ADD(power);

	if (local->ops->wake_tx_queue)
		DEBUGFS_ADD_MODE(aqm, 0600);

	statsd = debugfs_create_dir("statistics", phyd);

	/* if the dir failed, don't put all the other things into the root! */
	if (!statsd)
		return;

#ifdef CONFIG_MAC80211_DEBUG_COUNTERS
	DEBUGFS_STATS_ADD(dot11TransmittedFragmentCount);
	DEBUGFS_STATS_ADD(dot11MulticastTransmittedFrameCount);
	DEBUGFS_STATS_ADD(dot11FailedCount);
	DEBUGFS_STATS_ADD(dot11RetryCount);
	DEBUGFS_STATS_ADD(dot11MultipleRetryCount);
	DEBUGFS_STATS_ADD(dot11FrameDuplicateCount);
	DEBUGFS_STATS_ADD(dot11ReceivedFragmentCount);
	DEBUGFS_STATS_ADD(dot11MulticastReceivedFrameCount);
	DEBUGFS_STATS_ADD(dot11TransmittedFrameCount);
	DEBUGFS_STATS_ADD(tx_handlers_drop);
	DEBUGFS_STATS_ADD(tx_handlers_queued);
	DEBUGFS_STATS_ADD(tx_handlers_drop_wep);
	DEBUGFS_STATS_ADD(tx_handlers_drop_not_assoc);
	DEBUGFS_STATS_ADD(tx_handlers_drop_unauth_port);
	DEBUGFS_STATS_ADD(rx_handlers_drop);
	DEBUGFS_STATS_ADD(rx_handlers_queued);
	DEBUGFS_STATS_ADD(rx_handlers_drop_nullfunc);
	DEBUGFS_STATS_ADD(rx_handlers_drop_defrag);
	DEBUGFS_STATS_ADD(tx_expand_skb_head);
	DEBUGFS_STATS_ADD(tx_expand_skb_head_cloned);
	DEBUGFS_STATS_ADD(rx_expand_skb_head_defrag);
	DEBUGFS_STATS_ADD(rx_handlers_fragments);
	DEBUGFS_STATS_ADD(tx_status_drop);
#endif
	DEBUGFS_DEVSTATS_ADD(dot11ACKFailureCount);
	DEBUGFS_DEVSTATS_ADD(dot11RTSFailureCount);
	DEBUGFS_DEVSTATS_ADD(dot11FCSErrorCount);
	DEBUGFS_DEVSTATS_ADD(dot11RTSSuccessCount);
}