#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mtk_eth {TYPE_3__** mac; TYPE_2__* soc; } ;
struct TYPE_6__ {TYPE_1__* hw_stats; } ;
struct TYPE_5__ {int mac_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  stats_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_stats_update_mac (TYPE_3__*) ; 
 scalar_t__ spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtk_stats_update(struct mtk_eth *eth)
{
	int i;

	for (i = 0; i < eth->soc->mac_count; i++) {
		if (!eth->mac[i] || !eth->mac[i]->hw_stats)
			continue;
		if (spin_trylock(&eth->mac[i]->hw_stats->stats_lock)) {
			mtk_stats_update_mac(eth->mac[i]);
			spin_unlock(&eth->mac[i]->hw_stats->stats_lock);
		}
	}
}