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
struct stats_record {int /*<<< orphan*/ * rxq; int /*<<< orphan*/  stats; } ;
struct TYPE_2__ {int max_entries; } ;

/* Variables and functions */
 TYPE_1__* bpf_map__def (int /*<<< orphan*/ ) ; 
 int bpf_map__fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_collect_percpu (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_queue_index_map ; 
 int /*<<< orphan*/  stats_global_map ; 

__attribute__((used)) static void stats_collect(struct stats_record *rec)
{
	int fd, i, max_rxqs;

	fd = bpf_map__fd(stats_global_map);
	map_collect_percpu(fd, 0, &rec->stats);

	fd = bpf_map__fd(rx_queue_index_map);
	max_rxqs = bpf_map__def(rx_queue_index_map)->max_entries;
	for (i = 0; i < max_rxqs; i++)
		map_collect_percpu(fd, i, &rec->rxq[i]);
}