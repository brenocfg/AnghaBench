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
struct cpu_map {int nr; int* map; } ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 int MAX_NR_CPUS ; 
 struct cpu_map* cpu_map__new (char*) ; 
 int /*<<< orphan*/  cpu_map__put (struct cpu_map*) ; 
 int /*<<< orphan*/  cpumask_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int str_to_bitmap(char *s, cpumask_t *b)
{
	int i;
	int ret = 0;
	struct cpu_map *m;
	int c;

	m = cpu_map__new(s);
	if (!m)
		return -1;

	for (i = 0; i < m->nr; i++) {
		c = m->map[i];
		if (c >= MAX_NR_CPUS) {
			ret = -1;
			break;
		}

		set_bit(c, cpumask_bits(b));
	}

	cpu_map__put(m);

	return ret;
}