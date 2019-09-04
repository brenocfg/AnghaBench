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
struct orangefs_kernel_op_s {int /*<<< orphan*/  waitq; int /*<<< orphan*/  op_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_VFS_STATE_SERVICED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void set_op_state_serviced(struct orangefs_kernel_op_s *op)
{
	op->op_state = OP_VFS_STATE_SERVICED;
	complete(&op->waitq);
}