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
struct task_cputime_atomic {int /*<<< orphan*/  sum_exec_runtime; int /*<<< orphan*/  stime; int /*<<< orphan*/  utime; } ;
struct task_cputime {void* sum_exec_runtime; void* stime; void* utime; } ;

/* Variables and functions */
 void* atomic64_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void sample_cputime_atomic(struct task_cputime *times,
					 struct task_cputime_atomic *atomic_times)
{
	times->utime = atomic64_read(&atomic_times->utime);
	times->stime = atomic64_read(&atomic_times->stime);
	times->sum_exec_runtime = atomic64_read(&atomic_times->sum_exec_runtime);
}