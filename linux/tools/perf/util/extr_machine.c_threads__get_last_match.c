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
struct threads {int dummy; } ;
struct thread {int dummy; } ;
struct machine {int dummy; } ;

/* Variables and functions */
 struct thread* __threads__get_last_match (struct threads*,struct machine*,int,int) ; 
 scalar_t__ perf_singlethreaded ; 

__attribute__((used)) static struct thread*
threads__get_last_match(struct threads *threads, struct machine *machine,
			int pid, int tid)
{
	struct thread *th = NULL;

	if (perf_singlethreaded)
		th = __threads__get_last_match(threads, machine, pid, tid);

	return th;
}