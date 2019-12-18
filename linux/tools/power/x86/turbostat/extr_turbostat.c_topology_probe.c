#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct cpu_topology {int dummy; } ;
struct TYPE_7__ {int logical_cpu_id; int physical_package_id; int die_id; scalar_t__ physical_node_id; int physical_core_id; scalar_t__ thread_id; int logical_node_id; } ;
struct TYPE_6__ {int num_cpus; int max_cpu_num; scalar_t__ max_node_num; int cores_per_node; int num_die; int num_packages; int nodes_per_pkg; int threads_per_core; int /*<<< orphan*/  num_cores; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIC_CPU ; 
 int /*<<< orphan*/  BIC_Core ; 
 int /*<<< orphan*/  BIC_Die ; 
 int /*<<< orphan*/  BIC_Node ; 
 int /*<<< orphan*/  BIC_PRESENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIC_Package ; 
 int /*<<< orphan*/ * CPU_ALLOC (int) ; 
 int /*<<< orphan*/  CPU_ALLOC_SIZE (int) ; 
 scalar_t__ CPU_ISSET_S (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int CPU_SUBSET_MAXCPUS ; 
 int /*<<< orphan*/  CPU_ZERO_S (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  count_cpus ; 
 int /*<<< orphan*/ * cpu_affinity_set ; 
 int /*<<< orphan*/  cpu_affinity_setsize ; 
 scalar_t__ cpu_is_not_present (int) ; 
 int /*<<< orphan*/ * cpu_present_set ; 
 int /*<<< orphan*/  cpu_present_setsize ; 
 int /*<<< orphan*/ * cpu_subset ; 
 int /*<<< orphan*/  cpu_subset_size ; 
 TYPE_2__* cpus ; 
 int debug ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  for_all_proc_cpus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int get_core_id (int) ; 
 int get_die_id (int) ; 
 scalar_t__ get_physical_node_id (TYPE_2__*) ; 
 int get_physical_package_id (int) ; 
 int get_thread_siblings (TYPE_2__*) ; 
 int /*<<< orphan*/  init_thread_id ; 
 int /*<<< orphan*/  mark_cpu_present ; 
 int /*<<< orphan*/  outf ; 
 int /*<<< orphan*/  set_max_cpu_num () ; 
 int /*<<< orphan*/  set_node_data () ; 
 int /*<<< orphan*/  summary_only ; 
 TYPE_1__ topo ; 

void topology_probe()
{
	int i;
	int max_core_id = 0;
	int max_package_id = 0;
	int max_die_id = 0;
	int max_siblings = 0;

	/* Initialize num_cpus, max_cpu_num */
	set_max_cpu_num();
	topo.num_cpus = 0;
	for_all_proc_cpus(count_cpus);
	if (!summary_only && topo.num_cpus > 1)
		BIC_PRESENT(BIC_CPU);

	if (debug > 1)
		fprintf(outf, "num_cpus %d max_cpu_num %d\n", topo.num_cpus, topo.max_cpu_num);

	cpus = calloc(1, (topo.max_cpu_num  + 1) * sizeof(struct cpu_topology));
	if (cpus == NULL)
		err(1, "calloc cpus");

	/*
	 * Allocate and initialize cpu_present_set
	 */
	cpu_present_set = CPU_ALLOC((topo.max_cpu_num + 1));
	if (cpu_present_set == NULL)
		err(3, "CPU_ALLOC");
	cpu_present_setsize = CPU_ALLOC_SIZE((topo.max_cpu_num + 1));
	CPU_ZERO_S(cpu_present_setsize, cpu_present_set);
	for_all_proc_cpus(mark_cpu_present);

	/*
	 * Validate that all cpus in cpu_subset are also in cpu_present_set
	 */
	for (i = 0; i < CPU_SUBSET_MAXCPUS; ++i) {
		if (CPU_ISSET_S(i, cpu_subset_size, cpu_subset))
			if (!CPU_ISSET_S(i, cpu_present_setsize, cpu_present_set))
				err(1, "cpu%d not present", i);
	}

	/*
	 * Allocate and initialize cpu_affinity_set
	 */
	cpu_affinity_set = CPU_ALLOC((topo.max_cpu_num + 1));
	if (cpu_affinity_set == NULL)
		err(3, "CPU_ALLOC");
	cpu_affinity_setsize = CPU_ALLOC_SIZE((topo.max_cpu_num + 1));
	CPU_ZERO_S(cpu_affinity_setsize, cpu_affinity_set);

	for_all_proc_cpus(init_thread_id);

	/*
	 * For online cpus
	 * find max_core_id, max_package_id
	 */
	for (i = 0; i <= topo.max_cpu_num; ++i) {
		int siblings;

		if (cpu_is_not_present(i)) {
			if (debug > 1)
				fprintf(outf, "cpu%d NOT PRESENT\n", i);
			continue;
		}

		cpus[i].logical_cpu_id = i;

		/* get package information */
		cpus[i].physical_package_id = get_physical_package_id(i);
		if (cpus[i].physical_package_id > max_package_id)
			max_package_id = cpus[i].physical_package_id;

		/* get die information */
		cpus[i].die_id = get_die_id(i);
		if (cpus[i].die_id > max_die_id)
			max_die_id = cpus[i].die_id;

		/* get numa node information */
		cpus[i].physical_node_id = get_physical_node_id(&cpus[i]);
		if (cpus[i].physical_node_id > topo.max_node_num)
			topo.max_node_num = cpus[i].physical_node_id;

		/* get core information */
		cpus[i].physical_core_id = get_core_id(i);
		if (cpus[i].physical_core_id > max_core_id)
			max_core_id = cpus[i].physical_core_id;

		/* get thread information */
		siblings = get_thread_siblings(&cpus[i]);
		if (siblings > max_siblings)
			max_siblings = siblings;
		if (cpus[i].thread_id == 0)
			topo.num_cores++;
	}

	topo.cores_per_node = max_core_id + 1;
	if (debug > 1)
		fprintf(outf, "max_core_id %d, sizing for %d cores per package\n",
			max_core_id, topo.cores_per_node);
	if (!summary_only && topo.cores_per_node > 1)
		BIC_PRESENT(BIC_Core);

	topo.num_die = max_die_id + 1;
	if (debug > 1)
		fprintf(outf, "max_die_id %d, sizing for %d die\n",
				max_die_id, topo.num_die);
	if (!summary_only && topo.num_die > 1)
		BIC_PRESENT(BIC_Die);

	topo.num_packages = max_package_id + 1;
	if (debug > 1)
		fprintf(outf, "max_package_id %d, sizing for %d packages\n",
			max_package_id, topo.num_packages);
	if (!summary_only && topo.num_packages > 1)
		BIC_PRESENT(BIC_Package);

	set_node_data();
	if (debug > 1)
		fprintf(outf, "nodes_per_pkg %d\n", topo.nodes_per_pkg);
	if (!summary_only && topo.nodes_per_pkg > 1)
		BIC_PRESENT(BIC_Node);

	topo.threads_per_core = max_siblings;
	if (debug > 1)
		fprintf(outf, "max_siblings %d\n", max_siblings);

	if (debug < 1)
		return;

	for (i = 0; i <= topo.max_cpu_num; ++i) {
		if (cpu_is_not_present(i))
			continue;
		fprintf(outf,
			"cpu %d pkg %d die %d node %d lnode %d core %d thread %d\n",
			i, cpus[i].physical_package_id, cpus[i].die_id,
			cpus[i].physical_node_id,
			cpus[i].logical_node_id,
			cpus[i].physical_core_id,
			cpus[i].thread_id);
	}

}