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
struct uprobe_consumer {int /*<<< orphan*/  ret_handler; int /*<<< orphan*/  handler; } ;
struct uprobe {int /*<<< orphan*/  register_rwsem; } ;
struct inode {TYPE_2__* i_mapping; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_4__ {TYPE_1__* a_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  readpage; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct uprobe*) ; 
 int PTR_ERR (struct uprobe*) ; 
 int /*<<< orphan*/  __uprobe_unregister (struct uprobe*,struct uprobe_consumer*) ; 
 struct uprobe* alloc_uprobe (struct inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  consumer_add (struct uprobe*,struct uprobe_consumer*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_uprobe (struct uprobe*) ; 
 int register_for_each_vma (struct uprobe*,struct uprobe_consumer*) ; 
 int /*<<< orphan*/  shmem_mapping (TYPE_2__*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uprobe_is_active (struct uprobe*) ; 

__attribute__((used)) static int __uprobe_register(struct inode *inode, loff_t offset,
			     loff_t ref_ctr_offset, struct uprobe_consumer *uc)
{
	struct uprobe *uprobe;
	int ret;

	/* Uprobe must have at least one set consumer */
	if (!uc->handler && !uc->ret_handler)
		return -EINVAL;

	/* copy_insn() uses read_mapping_page() or shmem_read_mapping_page() */
	if (!inode->i_mapping->a_ops->readpage && !shmem_mapping(inode->i_mapping))
		return -EIO;
	/* Racy, just to catch the obvious mistakes */
	if (offset > i_size_read(inode))
		return -EINVAL;

 retry:
	uprobe = alloc_uprobe(inode, offset, ref_ctr_offset);
	if (!uprobe)
		return -ENOMEM;
	if (IS_ERR(uprobe))
		return PTR_ERR(uprobe);

	/*
	 * We can race with uprobe_unregister()->delete_uprobe().
	 * Check uprobe_is_active() and retry if it is false.
	 */
	down_write(&uprobe->register_rwsem);
	ret = -EAGAIN;
	if (likely(uprobe_is_active(uprobe))) {
		consumer_add(uprobe, uc);
		ret = register_for_each_vma(uprobe, uc);
		if (ret)
			__uprobe_unregister(uprobe, uc);
	}
	up_write(&uprobe->register_rwsem);
	put_uprobe(uprobe);

	if (unlikely(ret == -EAGAIN))
		goto retry;
	return ret;
}