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
struct machine {scalar_t__ comm_exec; } ;
struct comm {int dummy; } ;

/* Variables and functions */
 struct comm* thread__comm (struct thread*) ; 
 struct comm* thread__exec_comm (struct thread*) ; 

struct comm *machine__thread_exec_comm(struct machine *machine,
				       struct thread *thread)
{
	if (machine->comm_exec)
		return thread__exec_comm(thread);
	else
		return thread__comm(thread);
}