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
typedef  scalar_t__ uid_t ;
struct perf_thread_map {int dummy; } ;

/* Variables and functions */
 scalar_t__ UINT_MAX ; 
 struct perf_thread_map* thread_map__new_all_cpus () ; 
 struct perf_thread_map* thread_map__new_by_pid_str (char const*) ; 
 struct perf_thread_map* thread_map__new_by_tid_str (char const*) ; 
 struct perf_thread_map* thread_map__new_by_uid (scalar_t__) ; 

struct perf_thread_map *thread_map__new_str(const char *pid, const char *tid,
				       uid_t uid, bool all_threads)
{
	if (pid)
		return thread_map__new_by_pid_str(pid);

	if (!tid && uid != UINT_MAX)
		return thread_map__new_by_uid(uid);

	if (all_threads)
		return thread_map__new_all_cpus();

	return thread_map__new_by_tid_str(tid);
}