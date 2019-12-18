#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct poll_table_struct {int dummy; } ;
struct file {int f_mode; } ;
typedef  int __poll_t ;
struct TYPE_3__ {scalar_t__ locked; scalar_t__ count; scalar_t__ max_active; scalar_t__ block_size; scalar_t__ rear_size; int /*<<< orphan*/  action_queue; } ;

/* Variables and functions */
 int EPOLLOUT ; 
 int EPOLLWRNORM ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 
 int sq_setup (TYPE_1__*) ; 
 TYPE_1__ write_sq ; 

__attribute__((used)) static __poll_t sq_poll(struct file *file, struct poll_table_struct *wait)
{
	__poll_t mask = 0;
	int retVal;
	
	if (write_sq.locked == 0) {
		if ((retVal = sq_setup(&write_sq)) < 0)
			return retVal;
		return 0;
	}
	if (file->f_mode & FMODE_WRITE )
		poll_wait(file, &write_sq.action_queue, wait);
	if (file->f_mode & FMODE_WRITE)
		if (write_sq.count < write_sq.max_active || write_sq.block_size - write_sq.rear_size > 0)
			mask |= EPOLLOUT | EPOLLWRNORM;
	return mask;

}