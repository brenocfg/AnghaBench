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
struct thread {int dummy; } ;
struct db_export {int (* export_comm_thread ) (struct db_export*,scalar_t__,struct comm*,struct thread*) ;scalar_t__ comm_thread_last_db_id; } ;
struct comm {int dummy; } ;

/* Variables and functions */
 int stub1 (struct db_export*,scalar_t__,struct comm*,struct thread*) ; 

int db_export__comm_thread(struct db_export *dbe, struct comm *comm,
			   struct thread *thread)
{
	u64 db_id;

	db_id = ++dbe->comm_thread_last_db_id;

	if (dbe->export_comm_thread)
		return dbe->export_comm_thread(dbe, db_id, comm, thread);

	return 0;
}