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
struct thread_map {int dummy; } ;
typedef  int pid_t ;

/* Variables and functions */
 scalar_t__ UINT_MAX ; 
 struct thread_map* thread_map__new_by_pid (int) ; 
 struct thread_map* thread_map__new_by_tid (int) ; 
 struct thread_map* thread_map__new_by_uid (scalar_t__) ; 

struct thread_map *thread_map__new(pid_t pid, pid_t tid, uid_t uid)
{
	if (pid != -1)
		return thread_map__new_by_pid(pid);

	if (tid == -1 && uid != UINT_MAX)
		return thread_map__new_by_uid(uid);

	return thread_map__new_by_tid(tid);
}