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
struct threads {int /*<<< orphan*/  lock; } ;
struct thread {int dummy; } ;
struct machine {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 struct thread* ____machine__findnew_thread (struct machine*,struct threads*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct threads* machine__threads (struct machine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

struct thread *machine__find_thread(struct machine *machine, pid_t pid,
				    pid_t tid)
{
	struct threads *threads = machine__threads(machine, tid);
	struct thread *th;

	down_read(&threads->lock);
	th =  ____machine__findnew_thread(machine, threads, pid, tid, false);
	up_read(&threads->lock);
	return th;
}