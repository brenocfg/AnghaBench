#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fscache_state {int dummy; } ;
struct fscache_operation {int flags; } ;
struct fscache_object {TYPE_2__* cache; int /*<<< orphan*/  flags; struct fscache_cookie* cookie; int /*<<< orphan*/  debug_id; } ;
struct fscache_cookie {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  stores; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  invalidate_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSCACHE_COOKIE_INVALIDATING ; 
 int /*<<< orphan*/  FSCACHE_COOKIE_NO_DATA_YET ; 
 int /*<<< orphan*/  FSCACHE_OBJECT_PENDING_WRITE ; 
 int /*<<< orphan*/  FSCACHE_OBJECT_RETIRED ; 
 int FSCACHE_OP_ASYNC ; 
 int FSCACHE_OP_EXCLUSIVE ; 
 int FSCACHE_OP_UNUSE_COOKIE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KILL_OBJECT ; 
 int /*<<< orphan*/  UPDATE_OBJECT ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_cancel_all_ops (struct fscache_object*) ; 
 int /*<<< orphan*/  fscache_invalidate_writes (struct fscache_cookie*) ; 
 int /*<<< orphan*/  fscache_mark_object_dead (struct fscache_object*) ; 
 int /*<<< orphan*/  fscache_operation_init (struct fscache_cookie*,struct fscache_operation*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_page_op_invalidate ; 
 int /*<<< orphan*/  fscache_put_operation (struct fscache_operation*) ; 
 scalar_t__ fscache_submit_exclusive_op (struct fscache_object*,struct fscache_operation*) ; 
 int /*<<< orphan*/  fscache_unuse_cookie (struct fscache_object*) ; 
 int /*<<< orphan*/  fscache_use_cookie (struct fscache_object*) ; 
 int /*<<< orphan*/  kfree (struct fscache_operation*) ; 
 struct fscache_operation* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_fscache_page_op (struct fscache_cookie*,int /*<<< orphan*/ *,struct fscache_operation*,int /*<<< orphan*/ ) ; 
 struct fscache_state const* transit_to (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct fscache_state *_fscache_invalidate_object(struct fscache_object *object,
							      int event)
{
	struct fscache_operation *op;
	struct fscache_cookie *cookie = object->cookie;

	_enter("{OBJ%x},%d", object->debug_id, event);

	/* We're going to need the cookie.  If the cookie is not available then
	 * retire the object instead.
	 */
	if (!fscache_use_cookie(object)) {
		ASSERT(radix_tree_empty(&object->cookie->stores));
		set_bit(FSCACHE_OBJECT_RETIRED, &object->flags);
		_leave(" [no cookie]");
		return transit_to(KILL_OBJECT);
	}

	/* Reject any new read/write ops and abort any that are pending. */
	fscache_invalidate_writes(cookie);
	clear_bit(FSCACHE_OBJECT_PENDING_WRITE, &object->flags);
	fscache_cancel_all_ops(object);

	/* Now we have to wait for in-progress reads and writes */
	op = kzalloc(sizeof(*op), GFP_KERNEL);
	if (!op)
		goto nomem;

	fscache_operation_init(cookie, op, object->cache->ops->invalidate_object,
			       NULL, NULL);
	op->flags = FSCACHE_OP_ASYNC |
		(1 << FSCACHE_OP_EXCLUSIVE) |
		(1 << FSCACHE_OP_UNUSE_COOKIE);
	trace_fscache_page_op(cookie, NULL, op, fscache_page_op_invalidate);

	spin_lock(&cookie->lock);
	if (fscache_submit_exclusive_op(object, op) < 0)
		goto submit_op_failed;
	spin_unlock(&cookie->lock);
	fscache_put_operation(op);

	/* Once we've completed the invalidation, we know there will be no data
	 * stored in the cache and thus we can reinstate the data-check-skip
	 * optimisation.
	 */
	set_bit(FSCACHE_COOKIE_NO_DATA_YET, &cookie->flags);

	/* We can allow read and write requests to come in once again.  They'll
	 * queue up behind our exclusive invalidation operation.
	 */
	if (test_and_clear_bit(FSCACHE_COOKIE_INVALIDATING, &cookie->flags))
		wake_up_bit(&cookie->flags, FSCACHE_COOKIE_INVALIDATING);
	_leave(" [ok]");
	return transit_to(UPDATE_OBJECT);

nomem:
	fscache_mark_object_dead(object);
	fscache_unuse_cookie(object);
	_leave(" [ENOMEM]");
	return transit_to(KILL_OBJECT);

submit_op_failed:
	fscache_mark_object_dead(object);
	spin_unlock(&cookie->lock);
	fscache_unuse_cookie(object);
	kfree(op);
	_leave(" [EIO]");
	return transit_to(KILL_OBJECT);
}