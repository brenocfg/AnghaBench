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
struct thread {scalar_t__ db_id; } ;
struct machine {int dummy; } ;
struct db_export {int (* export_thread ) (struct db_export*,struct thread*,scalar_t__,struct machine*) ;scalar_t__ thread_last_db_id; } ;

/* Variables and functions */
 int stub1 (struct db_export*,struct thread*,scalar_t__,struct machine*) ; 

int db_export__thread(struct db_export *dbe, struct thread *thread,
		      struct machine *machine, struct thread *main_thread)
{
	u64 main_thread_db_id = 0;

	if (thread->db_id)
		return 0;

	thread->db_id = ++dbe->thread_last_db_id;

	if (main_thread)
		main_thread_db_id = main_thread->db_id;

	if (dbe->export_thread)
		return dbe->export_thread(dbe, thread, main_thread_db_id,
					  machine);

	return 0;
}