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
struct cpu_topo {int cpu_nr; void* thread_siblings; void* core_siblings; } ;
struct cpu_map {int dummy; } ;

/* Variables and functions */
 long UINT_MAX ; 
 int build_cpu_topo (struct cpu_topo*,int) ; 
 void* calloc (int,int) ; 
 long cpu__max_present_cpu () ; 
 int /*<<< orphan*/  cpu_map__has (struct cpu_map*,int) ; 
 struct cpu_map* cpu_map__new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_map__put (struct cpu_map*) ; 
 int /*<<< orphan*/  free_cpu_topo (struct cpu_topo*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static struct cpu_topo *build_cpu_topology(void)
{
	struct cpu_topo *tp = NULL;
	void *addr;
	u32 nr, i;
	size_t sz;
	long ncpus;
	int ret = -1;
	struct cpu_map *map;

	ncpus = cpu__max_present_cpu();

	/* build online CPU map */
	map = cpu_map__new(NULL);
	if (map == NULL) {
		pr_debug("failed to get system cpumap\n");
		return NULL;
	}

	nr = (u32)(ncpus & UINT_MAX);

	sz = nr * sizeof(char *);
	addr = calloc(1, sizeof(*tp) + 2 * sz);
	if (!addr)
		goto out_free;

	tp = addr;
	tp->cpu_nr = nr;
	addr += sizeof(*tp);
	tp->core_siblings = addr;
	addr += sz;
	tp->thread_siblings = addr;

	for (i = 0; i < nr; i++) {
		if (!cpu_map__has(map, i))
			continue;

		ret = build_cpu_topo(tp, i);
		if (ret < 0)
			break;
	}

out_free:
	cpu_map__put(map);
	if (ret) {
		free_cpu_topo(tp);
		tp = NULL;
	}
	return tp;
}