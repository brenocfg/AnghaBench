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

int db_export__comm(struct db_export *dbe, struct comm *comm,
		    struct thread *thread)
{
	if (comm->db_id)
		return 0;

	return __db_export__comm(dbe, comm, thread);
}