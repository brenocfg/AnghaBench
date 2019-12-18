#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {TYPE_3__* page; TYPE_1__* vma; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {int /*<<< orphan*/  cache; TYPE_2__ fid; } ;
struct TYPE_12__ {int /*<<< orphan*/  index; } ;
struct TYPE_10__ {struct file* vm_file; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (struct inode*) ; 
 unsigned long AFS_PRIV_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PG_writeback ; 
 scalar_t__ PageWriteback (TYPE_3__*) ; 
 int /*<<< orphan*/  SetPagePrivate (TYPE_3__*) ; 
 int /*<<< orphan*/  VM_FAULT_LOCKED ; 
 int /*<<< orphan*/  VM_FAULT_RETRY ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  fscache_wait_on_page_write (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ lock_page_killable (TYPE_3__*) ; 
 int /*<<< orphan*/  sb_end_pagefault (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_pagefault (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_private (TYPE_3__*,unsigned long) ; 
 int /*<<< orphan*/  trace_afs_page_dirty (struct afs_vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tracepoint_string (char*) ; 
 scalar_t__ wait_on_page_bit_killable (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_on_page_writeback (TYPE_3__*) ; 

vm_fault_t afs_page_mkwrite(struct vm_fault *vmf)
{
	struct file *file = vmf->vma->vm_file;
	struct inode *inode = file_inode(file);
	struct afs_vnode *vnode = AFS_FS_I(inode);
	unsigned long priv;

	_enter("{{%llx:%llu}},{%lx}",
	       vnode->fid.vid, vnode->fid.vnode, vmf->page->index);

	sb_start_pagefault(inode->i_sb);

	/* Wait for the page to be written to the cache before we allow it to
	 * be modified.  We then assume the entire page will need writing back.
	 */
#ifdef CONFIG_AFS_FSCACHE
	fscache_wait_on_page_write(vnode->cache, vmf->page);
#endif

	if (PageWriteback(vmf->page) &&
	    wait_on_page_bit_killable(vmf->page, PG_writeback) < 0)
		return VM_FAULT_RETRY;

	if (lock_page_killable(vmf->page) < 0)
		return VM_FAULT_RETRY;

	/* We mustn't change page->private until writeback is complete as that
	 * details the portion of the page we need to write back and we might
	 * need to redirty the page if there's a problem.
	 */
	wait_on_page_writeback(vmf->page);

	priv = (unsigned long)PAGE_SIZE << AFS_PRIV_SHIFT; /* To */
	priv |= 0; /* From */
	trace_afs_page_dirty(vnode, tracepoint_string("mkwrite"),
			     vmf->page->index, priv);
	SetPagePrivate(vmf->page);
	set_page_private(vmf->page, priv);

	sb_end_pagefault(inode->i_sb);
	return VM_FAULT_LOCKED;
}