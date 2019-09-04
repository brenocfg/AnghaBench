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
struct thread {int /*<<< orphan*/  comm_lock; } ;
struct rw_semaphore {int dummy; } ;

/* Variables and functions */
 char* __thread__comm_str (struct thread const*) ; 
 int /*<<< orphan*/  down_read (struct rw_semaphore*) ; 
 int /*<<< orphan*/  up_read (struct rw_semaphore*) ; 

const char *thread__comm_str(const struct thread *thread)
{
	const char *str;

	down_read((struct rw_semaphore *)&thread->comm_lock);
	str = __thread__comm_str(thread);
	up_read((struct rw_semaphore *)&thread->comm_lock);

	return str;
}