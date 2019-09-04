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
struct pcpu_sw_netstats {int tx_bytes; int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_packets; } ;
struct net_device {int /*<<< orphan*/  tstats; } ;

/* Variables and functions */
 int NET_XMIT_CN ; 
 int NET_XMIT_SUCCESS ; 
 scalar_t__ likely (int) ; 
 struct pcpu_sw_netstats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void count_tx(struct net_device *dev, int ret, int len)
{
	if (likely(ret == NET_XMIT_SUCCESS || ret == NET_XMIT_CN)) {
		struct pcpu_sw_netstats *stats = this_cpu_ptr(dev->tstats);

		u64_stats_update_begin(&stats->syncp);
		stats->tx_packets++;
		stats->tx_bytes += len;
		u64_stats_update_end(&stats->syncp);
	}
}