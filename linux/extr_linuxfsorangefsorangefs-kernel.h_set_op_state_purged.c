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
struct orangefs_kernel_op_s {int /*<<< orphan*/  lock; int /*<<< orphan*/  waitq; int /*<<< orphan*/  op_state; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_VFS_STATE_PURGED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  op_is_cancel (struct orangefs_kernel_op_s*) ; 
 int /*<<< orphan*/  put_cancel (struct orangefs_kernel_op_s*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_op_state_purged(struct orangefs_kernel_op_s *op)
{
	spin_lock(&op->lock);
	if (unlikely(op_is_cancel(op))) {
		list_del_init(&op->list);
		spin_unlock(&op->lock);
		put_cancel(op);
	} else {
		op->op_state |= OP_VFS_STATE_PURGED;
		complete(&op->waitq);
		spin_unlock(&op->lock);
	}
}