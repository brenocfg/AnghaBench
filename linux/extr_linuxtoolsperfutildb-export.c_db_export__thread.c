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
typedef  scalar_t__ u64 ;
struct thread {int pid_; int tid; scalar_t__ db_id; } ;
struct machine {int dummy; } ;
struct db_export {int (* export_thread ) (struct db_export*,struct thread*,scalar_t__,struct machine*) ;scalar_t__ thread_last_db_id; } ;
struct comm {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int db_export__comm_thread (struct db_export*,struct comm*,struct thread*) ; 
 struct thread* machine__findnew_thread (struct machine*,int,int) ; 
 int stub1 (struct db_export*,struct thread*,scalar_t__,struct machine*) ; 
 int /*<<< orphan*/  thread__put (struct thread*) ; 

int db_export__thread(struct db_export *dbe, struct thread *thread,
		      struct machine *machine, struct comm *comm)
{
	struct thread *main_thread;
	u64 main_thread_db_id = 0;
	int err;

	if (thread->db_id)
		return 0;

	thread->db_id = ++dbe->thread_last_db_id;

	if (thread->pid_ != -1) {
		if (thread->pid_ == thread->tid) {
			main_thread = thread;
		} else {
			main_thread = machine__findnew_thread(machine,
							      thread->pid_,
							      thread->pid_);
			if (!main_thread)
				return -ENOMEM;
			err = db_export__thread(dbe, main_thread, machine,
						comm);
			if (err)
				goto out_put;
			if (comm) {
				err = db_export__comm_thread(dbe, comm, thread);
				if (err)
					goto out_put;
			}
		}
		main_thread_db_id = main_thread->db_id;
		if (main_thread != thread)
			thread__put(main_thread);
	}

	if (dbe->export_thread)
		return dbe->export_thread(dbe, thread, main_thread_db_id,
					  machine);

	return 0;

out_put:
	thread__put(main_thread);
	return err;
}