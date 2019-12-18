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
struct perf_thread_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UINT_MAX ; 
 struct perf_thread_map* __thread_map__new_all_cpus (int /*<<< orphan*/ ) ; 

struct perf_thread_map *thread_map__new_all_cpus(void)
{
	return __thread_map__new_all_cpus(UINT_MAX);
}