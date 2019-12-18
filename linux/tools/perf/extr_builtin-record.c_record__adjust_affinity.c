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
struct TYPE_2__ {scalar_t__ affinity; } ;
struct record {int /*<<< orphan*/  affinity_mask; TYPE_1__ opts; } ;
struct mmap {int /*<<< orphan*/  affinity_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_OR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ PERF_AFFINITY_SYS ; 
 int /*<<< orphan*/  sched_setaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void record__adjust_affinity(struct record *rec, struct mmap *map)
{
	if (rec->opts.affinity != PERF_AFFINITY_SYS &&
	    !CPU_EQUAL(&rec->affinity_mask, &map->affinity_mask)) {
		CPU_ZERO(&rec->affinity_mask);
		CPU_OR(&rec->affinity_mask, &rec->affinity_mask, &map->affinity_mask);
		sched_setaffinity(0, sizeof(rec->affinity_mask), &rec->affinity_mask);
	}
}