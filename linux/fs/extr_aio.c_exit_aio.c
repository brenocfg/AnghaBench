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
struct mm_struct {int /*<<< orphan*/  ioctx_table; } ;
struct kioctx_table {int nr; int /*<<< orphan*/ * table; } ;
struct kioctx {scalar_t__ mmap_size; } ;
struct ctx_rq_wait {int /*<<< orphan*/  comp; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_sub_and_test (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct kioctx_table*) ; 
 int /*<<< orphan*/  kill_ioctx (struct mm_struct*,struct kioctx*,struct ctx_rq_wait*) ; 
 struct kioctx* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 struct kioctx_table* rcu_dereference_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void exit_aio(struct mm_struct *mm)
{
	struct kioctx_table *table = rcu_dereference_raw(mm->ioctx_table);
	struct ctx_rq_wait wait;
	int i, skipped;

	if (!table)
		return;

	atomic_set(&wait.count, table->nr);
	init_completion(&wait.comp);

	skipped = 0;
	for (i = 0; i < table->nr; ++i) {
		struct kioctx *ctx =
			rcu_dereference_protected(table->table[i], true);

		if (!ctx) {
			skipped++;
			continue;
		}

		/*
		 * We don't need to bother with munmap() here - exit_mmap(mm)
		 * is coming and it'll unmap everything. And we simply can't,
		 * this is not necessarily our ->mm.
		 * Since kill_ioctx() uses non-zero ->mmap_size as indicator
		 * that it needs to unmap the area, just set it to 0.
		 */
		ctx->mmap_size = 0;
		kill_ioctx(mm, ctx, &wait);
	}

	if (!atomic_sub_and_test(skipped, &wait.count)) {
		/* Wait until all IO for the context are done. */
		wait_for_completion(&wait.comp);
	}

	RCU_INIT_POINTER(mm->ioctx_table, NULL);
	kfree(table);
}