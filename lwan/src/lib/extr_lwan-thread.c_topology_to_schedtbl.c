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
typedef  size_t uint32_t ;
struct TYPE_2__ {size_t count; } ;
struct lwan {int n_cpus; TYPE_1__ thread; } ;

/* Variables and functions */
 size_t* alloca (int) ; 
 int /*<<< orphan*/  read_cpu_topology (struct lwan*,size_t*) ; 
 int /*<<< orphan*/  siblings_to_schedtbl (struct lwan*,size_t*,size_t*) ; 

__attribute__((used)) static void
topology_to_schedtbl(struct lwan *l, uint32_t schedtbl[], uint32_t n_threads)
{
    uint32_t *siblings = alloca(l->n_cpus * sizeof(uint32_t));

    if (!read_cpu_topology(l, siblings)) {
        for (uint32_t i = 0; i < n_threads; i++)
            schedtbl[i] = (i / 2) % l->thread.count;
    } else {
        uint32_t *affinity = alloca(l->n_cpus * sizeof(uint32_t));

        siblings_to_schedtbl(l, siblings, affinity);

        for (uint32_t i = 0; i < n_threads; i++)
            schedtbl[i] = affinity[i % l->n_cpus];
    }
}