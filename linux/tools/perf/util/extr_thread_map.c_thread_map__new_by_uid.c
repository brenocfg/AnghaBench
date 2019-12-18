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
typedef  int /*<<< orphan*/  uid_t ;
struct perf_thread_map {int dummy; } ;

/* Variables and functions */
 struct perf_thread_map* __thread_map__new_all_cpus (int /*<<< orphan*/ ) ; 

struct perf_thread_map *thread_map__new_by_uid(uid_t uid)
{
	return __thread_map__new_all_cpus(uid);
}