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
struct perf_thread_map {int nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  comm_init (struct perf_thread_map*,int) ; 

void thread_map__read_comms(struct perf_thread_map *threads)
{
	int i;

	for (i = 0; i < threads->nr; ++i)
		comm_init(threads, i);
}