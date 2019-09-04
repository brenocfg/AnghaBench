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
struct thread_data {int cpu_id; } ;
struct pkg_data {int package_id; } ;
struct core_data {int core_id; } ;
struct TYPE_2__ {int cores_per_node; int nodes_per_pkg; int num_packages; int threads_per_core; } ;

/* Variables and functions */
 void* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 TYPE_1__ topo ; 

void
allocate_counters(struct thread_data **t, struct core_data **c,
		  struct pkg_data **p)
{
	int i;
	int num_cores = topo.cores_per_node * topo.nodes_per_pkg *
			topo.num_packages;
	int num_threads = topo.threads_per_core * num_cores;

	*t = calloc(num_threads, sizeof(struct thread_data));
	if (*t == NULL)
		goto error;

	for (i = 0; i < num_threads; i++)
		(*t)[i].cpu_id = -1;

	*c = calloc(num_cores, sizeof(struct core_data));
	if (*c == NULL)
		goto error;

	for (i = 0; i < num_cores; i++)
		(*c)[i].core_id = -1;

	*p = calloc(topo.num_packages, sizeof(struct pkg_data));
	if (*p == NULL)
		goto error;

	for (i = 0; i < topo.num_packages; i++)
		(*p)[i].package_id = i;

	return;
error:
	err(1, "calloc counters");
}