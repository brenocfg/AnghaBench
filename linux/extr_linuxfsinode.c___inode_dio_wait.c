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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct inode {int /*<<< orphan*/  i_dio_count; int /*<<< orphan*/  i_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  wq_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT_BIT (TYPE_1__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __I_DIO_WAKEUP ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bit_waitqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ q ; 
 int /*<<< orphan*/  schedule () ; 

__attribute__((used)) static void __inode_dio_wait(struct inode *inode)
{
	wait_queue_head_t *wq = bit_waitqueue(&inode->i_state, __I_DIO_WAKEUP);
	DEFINE_WAIT_BIT(q, &inode->i_state, __I_DIO_WAKEUP);

	do {
		prepare_to_wait(wq, &q.wq_entry, TASK_UNINTERRUPTIBLE);
		if (atomic_read(&inode->i_dio_count))
			schedule();
	} while (atomic_read(&inode->i_dio_count));
	finish_wait(wq, &q.wq_entry);
}