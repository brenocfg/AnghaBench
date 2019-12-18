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
struct perf_thread_map {int nr; TYPE_1__* map; } ;
struct TYPE_2__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

int thread_map__remove(struct perf_thread_map *threads, int idx)
{
	int i;

	if (threads->nr < 1)
		return -EINVAL;

	if (idx >= threads->nr)
		return -EINVAL;

	/*
	 * Free the 'idx' item and shift the rest up.
	 */
	zfree(&threads->map[idx].comm);

	for (i = idx; i < threads->nr - 1; i++)
		threads->map[i] = threads->map[i + 1];

	threads->nr--;
	return 0;
}