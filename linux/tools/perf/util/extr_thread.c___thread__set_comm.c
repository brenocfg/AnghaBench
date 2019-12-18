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
typedef  int /*<<< orphan*/  u64 ;
struct thread {int /*<<< orphan*/  comm_lock; } ;

/* Variables and functions */
 int ____thread__set_comm (struct thread*,char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int __thread__set_comm(struct thread *thread, const char *str, u64 timestamp,
		       bool exec)
{
	int ret;

	down_write(&thread->comm_lock);
	ret = ____thread__set_comm(thread, str, timestamp, exec);
	up_write(&thread->comm_lock);
	return ret;
}