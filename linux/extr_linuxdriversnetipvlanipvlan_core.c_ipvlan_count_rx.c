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
struct ipvl_pcpu_stats {unsigned int rx_bytes; int /*<<< orphan*/  syncp; int /*<<< orphan*/  rx_mcast; int /*<<< orphan*/  rx_pkts; } ;
struct ipvl_dev {TYPE_1__* pcpu_stats; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_errs; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 struct ipvl_pcpu_stats* this_cpu_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

void ipvlan_count_rx(const struct ipvl_dev *ipvlan,
			    unsigned int len, bool success, bool mcast)
{
	if (likely(success)) {
		struct ipvl_pcpu_stats *pcptr;

		pcptr = this_cpu_ptr(ipvlan->pcpu_stats);
		u64_stats_update_begin(&pcptr->syncp);
		pcptr->rx_pkts++;
		pcptr->rx_bytes += len;
		if (mcast)
			pcptr->rx_mcast++;
		u64_stats_update_end(&pcptr->syncp);
	} else {
		this_cpu_inc(ipvlan->pcpu_stats->rx_errs);
	}
}