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
struct fscache_operation {scalar_t__ state; int /*<<< orphan*/  flags; } ;
struct fscache_object {int /*<<< orphan*/  cookie; } ;
typedef  enum fscache_operation_state { ____Placeholder_fscache_operation_state } fscache_operation_state ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int ENOBUFS ; 
 int ERESTARTSYS ; 
 scalar_t__ FSCACHE_OP_ST_CANCELLED ; 
 int /*<<< orphan*/  FSCACHE_OP_WAITING ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 scalar_t__ fscache_cache_is_broken (struct fscache_object*) ; 
 int fscache_cancel_op (struct fscache_operation*,int) ; 
 scalar_t__ fscache_object_is_dying (struct fscache_object*) ; 
 int /*<<< orphan*/  fscache_op_signal ; 
 int /*<<< orphan*/  fscache_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_fscache_op (int /*<<< orphan*/ ,struct fscache_operation*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int fscache_wait_for_operation_activation(struct fscache_object *object,
					  struct fscache_operation *op,
					  atomic_t *stat_op_waits,
					  atomic_t *stat_object_dead)
{
	int ret;

	if (!test_bit(FSCACHE_OP_WAITING, &op->flags))
		goto check_if_dead;

	_debug(">>> WT");
	if (stat_op_waits)
		fscache_stat(stat_op_waits);
	if (wait_on_bit(&op->flags, FSCACHE_OP_WAITING,
			TASK_INTERRUPTIBLE) != 0) {
		trace_fscache_op(object->cookie, op, fscache_op_signal);
		ret = fscache_cancel_op(op, false);
		if (ret == 0)
			return -ERESTARTSYS;

		/* it's been removed from the pending queue by another party,
		 * so we should get to run shortly */
		wait_on_bit(&op->flags, FSCACHE_OP_WAITING,
			    TASK_UNINTERRUPTIBLE);
	}
	_debug("<<< GO");

check_if_dead:
	if (op->state == FSCACHE_OP_ST_CANCELLED) {
		if (stat_object_dead)
			fscache_stat(stat_object_dead);
		_leave(" = -ENOBUFS [cancelled]");
		return -ENOBUFS;
	}
	if (unlikely(fscache_object_is_dying(object) ||
		     fscache_cache_is_broken(object))) {
		enum fscache_operation_state state = op->state;
		trace_fscache_op(object->cookie, op, fscache_op_signal);
		fscache_cancel_op(op, true);
		if (stat_object_dead)
			fscache_stat(stat_object_dead);
		_leave(" = -ENOBUFS [obj dead %d]", state);
		return -ENOBUFS;
	}
	return 0;
}