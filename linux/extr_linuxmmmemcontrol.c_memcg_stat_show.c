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
typedef  int u64 ;
struct seq_file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  max; } ;
struct TYPE_3__ {int /*<<< orphan*/  max; } ;
struct mem_cgroup {TYPE_2__ memsw; TYPE_1__ memory; } ;
struct accumulated_stats {unsigned int stats_size; scalar_t__* stats_array; unsigned int events_size; scalar_t__* events_array; scalar_t__* lru_pages; scalar_t__* events; scalar_t__* stat; } ;
typedef  int /*<<< orphan*/  acc ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ MEMCG_SWAP ; 
 unsigned int NR_LRU_LISTS ; 
 unsigned long PAGE_COUNTER_MAX ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  accumulate_memcg_tree (struct mem_cgroup*,struct accumulated_stats*) ; 
 scalar_t__ do_memsw_account () ; 
 struct mem_cgroup* mem_cgroup_from_css (int /*<<< orphan*/ ) ; 
 scalar_t__* mem_cgroup_lru_names ; 
 int mem_cgroup_nr_lru_pages (struct mem_cgroup*,int /*<<< orphan*/ ) ; 
 scalar_t__* memcg1_event_names ; 
 scalar_t__* memcg1_events ; 
 scalar_t__* memcg1_stat_names ; 
 scalar_t__* memcg1_stats ; 
 int memcg_page_state (struct mem_cgroup*,scalar_t__) ; 
 int memcg_sum_events (struct mem_cgroup*,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct accumulated_stats*,int /*<<< orphan*/ ,int) ; 
 unsigned long min (unsigned long,int /*<<< orphan*/ ) ; 
 struct mem_cgroup* parent_mem_cgroup (struct mem_cgroup*) ; 
 int /*<<< orphan*/  seq_css (struct seq_file*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__,...) ; 

__attribute__((used)) static int memcg_stat_show(struct seq_file *m, void *v)
{
	struct mem_cgroup *memcg = mem_cgroup_from_css(seq_css(m));
	unsigned long memory, memsw;
	struct mem_cgroup *mi;
	unsigned int i;
	struct accumulated_stats acc;

	BUILD_BUG_ON(ARRAY_SIZE(memcg1_stat_names) != ARRAY_SIZE(memcg1_stats));
	BUILD_BUG_ON(ARRAY_SIZE(mem_cgroup_lru_names) != NR_LRU_LISTS);

	for (i = 0; i < ARRAY_SIZE(memcg1_stats); i++) {
		if (memcg1_stats[i] == MEMCG_SWAP && !do_memsw_account())
			continue;
		seq_printf(m, "%s %lu\n", memcg1_stat_names[i],
			   memcg_page_state(memcg, memcg1_stats[i]) *
			   PAGE_SIZE);
	}

	for (i = 0; i < ARRAY_SIZE(memcg1_events); i++)
		seq_printf(m, "%s %lu\n", memcg1_event_names[i],
			   memcg_sum_events(memcg, memcg1_events[i]));

	for (i = 0; i < NR_LRU_LISTS; i++)
		seq_printf(m, "%s %lu\n", mem_cgroup_lru_names[i],
			   mem_cgroup_nr_lru_pages(memcg, BIT(i)) * PAGE_SIZE);

	/* Hierarchical information */
	memory = memsw = PAGE_COUNTER_MAX;
	for (mi = memcg; mi; mi = parent_mem_cgroup(mi)) {
		memory = min(memory, mi->memory.max);
		memsw = min(memsw, mi->memsw.max);
	}
	seq_printf(m, "hierarchical_memory_limit %llu\n",
		   (u64)memory * PAGE_SIZE);
	if (do_memsw_account())
		seq_printf(m, "hierarchical_memsw_limit %llu\n",
			   (u64)memsw * PAGE_SIZE);

	memset(&acc, 0, sizeof(acc));
	acc.stats_size = ARRAY_SIZE(memcg1_stats);
	acc.stats_array = memcg1_stats;
	acc.events_size = ARRAY_SIZE(memcg1_events);
	acc.events_array = memcg1_events;
	accumulate_memcg_tree(memcg, &acc);

	for (i = 0; i < ARRAY_SIZE(memcg1_stats); i++) {
		if (memcg1_stats[i] == MEMCG_SWAP && !do_memsw_account())
			continue;
		seq_printf(m, "total_%s %llu\n", memcg1_stat_names[i],
			   (u64)acc.stat[i] * PAGE_SIZE);
	}

	for (i = 0; i < ARRAY_SIZE(memcg1_events); i++)
		seq_printf(m, "total_%s %llu\n", memcg1_event_names[i],
			   (u64)acc.events[i]);

	for (i = 0; i < NR_LRU_LISTS; i++)
		seq_printf(m, "total_%s %llu\n", mem_cgroup_lru_names[i],
			   (u64)acc.lru_pages[i] * PAGE_SIZE);

#ifdef CONFIG_DEBUG_VM
	{
		pg_data_t *pgdat;
		struct mem_cgroup_per_node *mz;
		struct zone_reclaim_stat *rstat;
		unsigned long recent_rotated[2] = {0, 0};
		unsigned long recent_scanned[2] = {0, 0};

		for_each_online_pgdat(pgdat) {
			mz = mem_cgroup_nodeinfo(memcg, pgdat->node_id);
			rstat = &mz->lruvec.reclaim_stat;

			recent_rotated[0] += rstat->recent_rotated[0];
			recent_rotated[1] += rstat->recent_rotated[1];
			recent_scanned[0] += rstat->recent_scanned[0];
			recent_scanned[1] += rstat->recent_scanned[1];
		}
		seq_printf(m, "recent_rotated_anon %lu\n", recent_rotated[0]);
		seq_printf(m, "recent_rotated_file %lu\n", recent_rotated[1]);
		seq_printf(m, "recent_scanned_anon %lu\n", recent_scanned[0]);
		seq_printf(m, "recent_scanned_file %lu\n", recent_scanned[1]);
	}
#endif

	return 0;
}