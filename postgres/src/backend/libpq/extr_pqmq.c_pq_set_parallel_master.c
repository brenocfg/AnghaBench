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
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  BackendId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * PqCommMethods ; 
 int /*<<< orphan*/  PqCommMqMethods ; 
 int /*<<< orphan*/  pq_mq_parallel_master_backend_id ; 
 int /*<<< orphan*/  pq_mq_parallel_master_pid ; 

void
pq_set_parallel_master(pid_t pid, BackendId backend_id)
{
	Assert(PqCommMethods == &PqCommMqMethods);
	pq_mq_parallel_master_pid = pid;
	pq_mq_parallel_master_backend_id = backend_id;
}