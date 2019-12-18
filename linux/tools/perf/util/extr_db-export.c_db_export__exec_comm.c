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
struct thread {int dummy; } ;
struct db_export {int dummy; } ;
struct comm {scalar_t__ db_id; } ;

/* Variables and functions */
 int __db_export__comm (struct db_export*,struct comm*,struct thread*) ; 
 int db_export__comm_thread (struct db_export*,struct comm*,struct thread*) ; 

int db_export__exec_comm(struct db_export *dbe, struct comm *comm,
			 struct thread *main_thread)
{
	int err;

	if (comm->db_id)
		return 0;

	err = __db_export__comm(dbe, comm, main_thread);
	if (err)
		return err;

	/*
	 * Record the main thread for this comm. Note that the main thread can
	 * have many "exec" comms because there will be a new one every time it
	 * exec's. An "exec" comm however will only ever have 1 main thread.
	 * That is different to any other threads for that same program because
	 * exec() will effectively kill them, so the relationship between the
	 * "exec" comm and non-main threads is 1-to-1. That is why
	 * db_export__comm_thread() is called here for the main thread, but it
	 * is called for non-main threads when they are exported.
	 */
	return db_export__comm_thread(dbe, comm, main_thread);
}