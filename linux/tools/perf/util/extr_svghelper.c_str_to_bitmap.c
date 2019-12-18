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
struct perf_cpu_map {int nr; int* map; } ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_bits (int /*<<< orphan*/ *) ; 
 struct perf_cpu_map* perf_cpu_map__new (char*) ; 
 int /*<<< orphan*/  perf_cpu_map__put (struct perf_cpu_map*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int str_to_bitmap(char *s, cpumask_t *b, int nr_cpus)
{
	int i;
	int ret = 0;
	struct perf_cpu_map *m;
	int c;

	m = perf_cpu_map__new(s);
	if (!m)
		return -1;

	for (i = 0; i < m->nr; i++) {
		c = m->map[i];
		if (c >= nr_cpus) {
			ret = -1;
			break;
		}

		set_bit(c, cpumask_bits(b));
	}

	perf_cpu_map__put(m);

	return ret;
}