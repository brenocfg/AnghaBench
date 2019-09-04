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
struct TYPE_3__ {scalar_t__ nr_nodes; int show_details; long mb_global; long mb_proc; long mb_proc_locked; long mb_thread; int nr_threads; int nr_proc; int nr_tasks; long bytes_global; long bytes_process; long bytes_process_locked; long bytes_thread; scalar_t__ mb_thread_str; scalar_t__ mb_proc_locked_str; scalar_t__ mb_proc_str; scalar_t__ mb_global_str; scalar_t__ show_quiet; int /*<<< orphan*/  nr_cpus; } ;
struct TYPE_4__ {int /*<<< orphan*/  stop_work_mutex; int /*<<< orphan*/  startup_done_mutex; int /*<<< orphan*/  startup_mutex; int /*<<< orphan*/  start_work_mutex; TYPE_1__ p; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 scalar_t__ MAX_NR_NODES ; 
 scalar_t__ alloc_data (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* atof (scalar_t__) ; 
 TYPE_2__* g ; 
 int /*<<< orphan*/  init_global_mutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_thread_data () ; 
 scalar_t__ numa_max_node () ; 
 int /*<<< orphan*/  numa_num_configured_cpus () ; 
 TYPE_1__ p0 ; 
 scalar_t__ parse_setup_cpu_list () ; 
 scalar_t__ parse_setup_node_list () ; 
 int /*<<< orphan*/  print_summary () ; 
 int /*<<< orphan*/  setup_shared_data (long) ; 
 int /*<<< orphan*/  tprintf (char*) ; 

__attribute__((used)) static int init(void)
{
	g = (void *)alloc_data(sizeof(*g), MAP_SHARED, 1, 0, 0 /* THP */, 0);

	/* Copy over options: */
	g->p = p0;

	g->p.nr_cpus = numa_num_configured_cpus();

	g->p.nr_nodes = numa_max_node() + 1;

	/* char array in count_process_nodes(): */
	BUG_ON(g->p.nr_nodes > MAX_NR_NODES || g->p.nr_nodes < 0);

	if (g->p.show_quiet && !g->p.show_details)
		g->p.show_details = -1;

	/* Some memory should be specified: */
	if (!g->p.mb_global_str && !g->p.mb_proc_str && !g->p.mb_thread_str)
		return -1;

	if (g->p.mb_global_str) {
		g->p.mb_global = atof(g->p.mb_global_str);
		BUG_ON(g->p.mb_global < 0);
	}

	if (g->p.mb_proc_str) {
		g->p.mb_proc = atof(g->p.mb_proc_str);
		BUG_ON(g->p.mb_proc < 0);
	}

	if (g->p.mb_proc_locked_str) {
		g->p.mb_proc_locked = atof(g->p.mb_proc_locked_str);
		BUG_ON(g->p.mb_proc_locked < 0);
		BUG_ON(g->p.mb_proc_locked > g->p.mb_proc);
	}

	if (g->p.mb_thread_str) {
		g->p.mb_thread = atof(g->p.mb_thread_str);
		BUG_ON(g->p.mb_thread < 0);
	}

	BUG_ON(g->p.nr_threads <= 0);
	BUG_ON(g->p.nr_proc <= 0);

	g->p.nr_tasks = g->p.nr_proc*g->p.nr_threads;

	g->p.bytes_global		= g->p.mb_global	*1024L*1024L;
	g->p.bytes_process		= g->p.mb_proc		*1024L*1024L;
	g->p.bytes_process_locked	= g->p.mb_proc_locked	*1024L*1024L;
	g->p.bytes_thread		= g->p.mb_thread	*1024L*1024L;

	g->data = setup_shared_data(g->p.bytes_global);

	/* Startup serialization: */
	init_global_mutex(&g->start_work_mutex);
	init_global_mutex(&g->startup_mutex);
	init_global_mutex(&g->startup_done_mutex);
	init_global_mutex(&g->stop_work_mutex);

	init_thread_data();

	tprintf("#\n");
	if (parse_setup_cpu_list() || parse_setup_node_list())
		return -1;
	tprintf("#\n");

	print_summary();

	return 0;
}