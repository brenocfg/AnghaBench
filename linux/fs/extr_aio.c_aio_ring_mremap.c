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
struct vm_area_struct {int /*<<< orphan*/  vm_start; struct mm_struct* vm_mm; struct file* vm_file; } ;
struct mm_struct {int /*<<< orphan*/  ioctx_lock; int /*<<< orphan*/  ioctx_table; } ;
struct kioctx_table {int nr; int /*<<< orphan*/ * table; } ;
struct kioctx {int /*<<< orphan*/  mmap_base; int /*<<< orphan*/  user_id; int /*<<< orphan*/  dead; struct file* aio_ring_file; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aio_ring_mremap(struct vm_area_struct *vma)
{
	struct file *file = vma->vm_file;
	struct mm_struct *mm = vma->vm_mm;
	struct kioctx_table *table;
	int i, res = -EINVAL;

	spin_lock(&mm->ioctx_lock);
	rcu_read_lock();
	table = rcu_dereference(mm->ioctx_table);
	for (i = 0; i < table->nr; i++) {
		struct kioctx *ctx;

		ctx = rcu_dereference(table->table[i]);
		if (ctx && ctx->aio_ring_file == file) {
			if (!atomic_read(&ctx->dead)) {
				ctx->user_id = ctx->mmap_base = vma->vm_start;
				res = 0;
			}
			break;
		}
	}

	rcu_read_unlock();
	spin_unlock(&mm->ioctx_lock);
	return res;
}