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
typedef  int u32 ;
struct perf_cpu_map {int dummy; } ;
struct cpu_topology {void* thread_siblings; void* die_siblings; void* core_siblings; } ;

/* Variables and functions */
 long UINT_MAX ; 
 int build_cpu_topology (struct cpu_topology*,int) ; 
 void* calloc (int,int) ; 
 long cpu__max_present_cpu () ; 
 int /*<<< orphan*/  cpu_map__has (struct perf_cpu_map*,int) ; 
 int /*<<< orphan*/  cpu_topology__delete (struct cpu_topology*) ; 
 int has_die_topology () ; 
 struct perf_cpu_map* perf_cpu_map__new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_cpu_map__put (struct perf_cpu_map*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

struct cpu_topology *cpu_topology__new(void)
{
	struct cpu_topology *tp = NULL;
	void *addr;
	u32 nr, i, nr_addr;
	size_t sz;
	long ncpus;
	int ret = -1;
	struct perf_cpu_map *map;
	bool has_die = has_die_topology();

	ncpus = cpu__max_present_cpu();

	/* build online CPU map */
	map = perf_cpu_map__new(NULL);
	if (map == NULL) {
		pr_debug("failed to get system cpumap\n");
		return NULL;
	}

	nr = (u32)(ncpus & UINT_MAX);

	sz = nr * sizeof(char *);
	if (has_die)
		nr_addr = 3;
	else
		nr_addr = 2;
	addr = calloc(1, sizeof(*tp) + nr_addr * sz);
	if (!addr)
		goto out_free;

	tp = addr;
	addr += sizeof(*tp);
	tp->core_siblings = addr;
	addr += sz;
	if (has_die) {
		tp->die_siblings = addr;
		addr += sz;
	}
	tp->thread_siblings = addr;

	for (i = 0; i < nr; i++) {
		if (!cpu_map__has(map, i))
			continue;

		ret = build_cpu_topology(tp, i);
		if (ret < 0)
			break;
	}

out_free:
	perf_cpu_map__put(map);
	if (ret) {
		cpu_topology__delete(tp);
		tp = NULL;
	}
	return tp;
}