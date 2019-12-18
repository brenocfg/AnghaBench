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

/* Variables and functions */
 char* __thread__comm_str (struct thread*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

const char *thread__comm_str(struct thread *thread)
{
	const char *str;

	down_read(&thread->comm_lock);
	str = __thread__comm_str(thread);
	up_read(&thread->comm_lock);

	return str;
}