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
struct TYPE_2__ {int /*<<< orphan*/  refcnt; scalar_t__ base; } ;
struct mmap {TYPE_1__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  perf_mmap__munmap (struct mmap*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_read (int /*<<< orphan*/ *) ; 

void perf_mmap__put(struct mmap *map)
{
	BUG_ON(map->core.base && refcount_read(&map->core.refcnt) == 0);

	if (refcount_dec_and_test(&map->core.refcnt))
		perf_mmap__munmap(map);
}