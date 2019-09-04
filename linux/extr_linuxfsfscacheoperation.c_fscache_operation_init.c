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
struct fscache_operation {int /*<<< orphan*/  pend_link; int /*<<< orphan*/  release; int /*<<< orphan*/  cancel; int /*<<< orphan*/  processor; int /*<<< orphan*/  debug_id; int /*<<< orphan*/  state; int /*<<< orphan*/  usage; int /*<<< orphan*/  work; } ;
struct fscache_cookie {int dummy; } ;
typedef  int /*<<< orphan*/  fscache_operation_release_t ;
typedef  int /*<<< orphan*/  fscache_operation_processor_t ;
typedef  scalar_t__ fscache_operation_cancel_t ;

/* Variables and functions */
 int /*<<< orphan*/  FSCACHE_OP_ST_INITIALISED ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fscache_n_op_initialised ; 
 int /*<<< orphan*/  fscache_op_debug_id ; 
 int /*<<< orphan*/  fscache_op_init ; 
 int /*<<< orphan*/  fscache_op_work_func ; 
 int /*<<< orphan*/  fscache_operation_dummy_cancel ; 
 int /*<<< orphan*/  fscache_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_fscache_op (struct fscache_cookie*,struct fscache_operation*,int /*<<< orphan*/ ) ; 

void fscache_operation_init(struct fscache_cookie *cookie,
			    struct fscache_operation *op,
			    fscache_operation_processor_t processor,
			    fscache_operation_cancel_t cancel,
			    fscache_operation_release_t release)
{
	INIT_WORK(&op->work, fscache_op_work_func);
	atomic_set(&op->usage, 1);
	op->state = FSCACHE_OP_ST_INITIALISED;
	op->debug_id = atomic_inc_return(&fscache_op_debug_id);
	op->processor = processor;
	op->cancel = cancel ?: fscache_operation_dummy_cancel;
	op->release = release;
	INIT_LIST_HEAD(&op->pend_link);
	fscache_stat(&fscache_n_op_initialised);
	trace_fscache_op(cookie, op, fscache_op_init);
}