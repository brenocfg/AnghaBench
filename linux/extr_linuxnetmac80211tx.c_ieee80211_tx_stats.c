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
typedef  scalar_t__ u32 ;
struct pcpu_sw_netstats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {int /*<<< orphan*/  tstats; } ;

/* Variables and functions */
 struct pcpu_sw_netstats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ieee80211_tx_stats(struct net_device *dev, u32 len)
{
	struct pcpu_sw_netstats *tstats = this_cpu_ptr(dev->tstats);

	u64_stats_update_begin(&tstats->syncp);
	tstats->tx_packets++;
	tstats->tx_bytes += len;
	u64_stats_update_end(&tstats->syncp);
}