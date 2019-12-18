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
struct mm_struct {int /*<<< orphan*/  ioctx_lock; int /*<<< orphan*/  ioctx_table; } ;
struct kioctx_table {int /*<<< orphan*/ * table; } ;
struct kioctx {size_t id; int /*<<< orphan*/  users; struct ctx_rq_wait* rq_wait; scalar_t__ mmap_size; int /*<<< orphan*/  mmap_base; int /*<<< orphan*/  max_reqs; int /*<<< orphan*/  wait; int /*<<< orphan*/  dead; } ;
struct ctx_rq_wait {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  aio_nr_sub (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_xchg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  percpu_ref_kill (int /*<<< orphan*/ *) ; 
 struct kioctx* rcu_access_pointer (int /*<<< orphan*/ ) ; 
 struct kioctx_table* rcu_dereference_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_munmap (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kill_ioctx(struct mm_struct *mm, struct kioctx *ctx,
		      struct ctx_rq_wait *wait)
{
	struct kioctx_table *table;

	spin_lock(&mm->ioctx_lock);
	if (atomic_xchg(&ctx->dead, 1)) {
		spin_unlock(&mm->ioctx_lock);
		return -EINVAL;
	}

	table = rcu_dereference_raw(mm->ioctx_table);
	WARN_ON(ctx != rcu_access_pointer(table->table[ctx->id]));
	RCU_INIT_POINTER(table->table[ctx->id], NULL);
	spin_unlock(&mm->ioctx_lock);

	/* free_ioctx_reqs() will do the necessary RCU synchronization */
	wake_up_all(&ctx->wait);

	/*
	 * It'd be more correct to do this in free_ioctx(), after all
	 * the outstanding kiocbs have finished - but by then io_destroy
	 * has already returned, so io_setup() could potentially return
	 * -EAGAIN with no ioctxs actually in use (as far as userspace
	 *  could tell).
	 */
	aio_nr_sub(ctx->max_reqs);

	if (ctx->mmap_size)
		vm_munmap(ctx->mmap_base, ctx->mmap_size);

	ctx->rq_wait = wait;
	percpu_ref_kill(&ctx->users);
	return 0;
}