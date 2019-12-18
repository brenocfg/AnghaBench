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
struct TYPE_4__ {int nr_numa_nodes; int nr_cpus_avail; struct numa_node* numa_nodes; } ;
struct TYPE_5__ {TYPE_1__ env; } ;
struct perf_session {TYPE_2__ header; } ;
struct perf_cpu_map {int nr; size_t* map; } ;
struct numa_node {struct perf_cpu_map* map; } ;
struct TYPE_6__ {int node_info; int nodes_cnt; int cpus_cnt; unsigned long** nodes; int* cpu2node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ WARN_ONCE (int,char*) ; 
 unsigned long* bitmap_alloc (int) ; 
 TYPE_3__ c2c ; 
 scalar_t__ perf_cpu_map__empty (struct perf_cpu_map*) ; 
 int /*<<< orphan*/  set_bit (size_t,unsigned long*) ; 
 int /*<<< orphan*/  setup_nodes_header () ; 
 void* zalloc (int) ; 

__attribute__((used)) static int setup_nodes(struct perf_session *session)
{
	struct numa_node *n;
	unsigned long **nodes;
	int node, cpu;
	int *cpu2node;

	if (c2c.node_info > 2)
		c2c.node_info = 2;

	c2c.nodes_cnt = session->header.env.nr_numa_nodes;
	c2c.cpus_cnt  = session->header.env.nr_cpus_avail;

	n = session->header.env.numa_nodes;
	if (!n)
		return -EINVAL;

	nodes = zalloc(sizeof(unsigned long *) * c2c.nodes_cnt);
	if (!nodes)
		return -ENOMEM;

	c2c.nodes = nodes;

	cpu2node = zalloc(sizeof(int) * c2c.cpus_cnt);
	if (!cpu2node)
		return -ENOMEM;

	for (cpu = 0; cpu < c2c.cpus_cnt; cpu++)
		cpu2node[cpu] = -1;

	c2c.cpu2node = cpu2node;

	for (node = 0; node < c2c.nodes_cnt; node++) {
		struct perf_cpu_map *map = n[node].map;
		unsigned long *set;

		set = bitmap_alloc(c2c.cpus_cnt);
		if (!set)
			return -ENOMEM;

		nodes[node] = set;

		/* empty node, skip */
		if (perf_cpu_map__empty(map))
			continue;

		for (cpu = 0; cpu < map->nr; cpu++) {
			set_bit(map->map[cpu], set);

			if (WARN_ONCE(cpu2node[map->map[cpu]] != -1, "node/cpu topology bug"))
				return -EINVAL;

			cpu2node[map->map[cpu]] = node;
		}
	}

	setup_nodes_header();
	return 0;
}