#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct stats_record* cpu; } ;
struct stats_record {TYPE_1__ stats; struct stats_record* rxq; struct stats_record* cpu; } ;
struct TYPE_4__ {unsigned int max_entries; } ;

/* Variables and functions */
 TYPE_2__* bpf_map__def (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct stats_record*) ; 
 int /*<<< orphan*/  rx_queue_index_map ; 

__attribute__((used)) static void free_stats_record(struct stats_record *r)
{
	unsigned int nr_rxqs = bpf_map__def(rx_queue_index_map)->max_entries;
	int i;

	for (i = 0; i < nr_rxqs; i++)
		free(r->rxq[i].cpu);

	free(r->rxq);
	free(r->stats.cpu);
	free(r);
}