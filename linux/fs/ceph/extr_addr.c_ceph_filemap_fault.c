#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t vm_fault_t ;
struct vm_fault {scalar_t__ pgoff; struct page* page; struct vm_area_struct* vma; } ;
struct vm_area_struct {TYPE_1__* vm_file; } ;
struct page {int dummy; } ;
struct inode {struct address_space* i_mapping; } ;
struct ceph_inode_info {scalar_t__ i_inline_version; } ;
struct ceph_file_info {int fmode; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_3__ {struct ceph_file_info* private_data; } ;

/* Variables and functions */
 int CEPH_CAP_FILE_CACHE ; 
 int CEPH_CAP_FILE_LAZYIO ; 
 int /*<<< orphan*/  CEPH_CAP_FILE_RD ; 
 int /*<<< orphan*/  CEPH_DEFINE_RW_CONTEXT (int /*<<< orphan*/ ,int) ; 
 int CEPH_FILE_MODE_LAZY ; 
 scalar_t__ CEPH_INLINE_NONE ; 
 int /*<<< orphan*/  CEPH_STAT_CAP_INLINE_DATA ; 
 int EAGAIN ; 
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 size_t VM_FAULT_LOCKED ; 
 size_t VM_FAULT_MAJOR ; 
 size_t VM_FAULT_OOM ; 
 size_t VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  __GFP_FS ; 
 int __ceph_do_getattr (struct inode*,struct page*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ceph_add_rw_context (struct ceph_file_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_block_sigs (int /*<<< orphan*/ *) ; 
 size_t ceph_cap_string (int) ; 
 int /*<<< orphan*/  ceph_del_rw_context (struct ceph_file_info*,int /*<<< orphan*/ *) ; 
 int ceph_get_caps (TYPE_1__*,int /*<<< orphan*/ ,int,int,int*,struct page**) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  ceph_put_cap_refs (struct ceph_inode_info*,int) ; 
 int /*<<< orphan*/  ceph_restore_sigs (int /*<<< orphan*/ *) ; 
 scalar_t__ ceph_vinop (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,scalar_t__,size_t,size_t,...) ; 
 struct inode* file_inode (TYPE_1__*) ; 
 size_t filemap_fault (struct vm_fault*) ; 
 struct page* find_or_create_page (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mapping_gfp_constraint (struct address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  rw_ctx ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 size_t vmf_error (int) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,int,scalar_t__) ; 

__attribute__((used)) static vm_fault_t ceph_filemap_fault(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	struct inode *inode = file_inode(vma->vm_file);
	struct ceph_inode_info *ci = ceph_inode(inode);
	struct ceph_file_info *fi = vma->vm_file->private_data;
	struct page *pinned_page = NULL;
	loff_t off = vmf->pgoff << PAGE_SHIFT;
	int want, got, err;
	sigset_t oldset;
	vm_fault_t ret = VM_FAULT_SIGBUS;

	ceph_block_sigs(&oldset);

	dout("filemap_fault %p %llx.%llx %llu~%zd trying to get caps\n",
	     inode, ceph_vinop(inode), off, (size_t)PAGE_SIZE);
	if (fi->fmode & CEPH_FILE_MODE_LAZY)
		want = CEPH_CAP_FILE_CACHE | CEPH_CAP_FILE_LAZYIO;
	else
		want = CEPH_CAP_FILE_CACHE;

	got = 0;
	err = ceph_get_caps(vma->vm_file, CEPH_CAP_FILE_RD, want, -1,
			    &got, &pinned_page);
	if (err < 0)
		goto out_restore;

	dout("filemap_fault %p %llu~%zd got cap refs on %s\n",
	     inode, off, (size_t)PAGE_SIZE, ceph_cap_string(got));

	if ((got & (CEPH_CAP_FILE_CACHE | CEPH_CAP_FILE_LAZYIO)) ||
	    ci->i_inline_version == CEPH_INLINE_NONE) {
		CEPH_DEFINE_RW_CONTEXT(rw_ctx, got);
		ceph_add_rw_context(fi, &rw_ctx);
		ret = filemap_fault(vmf);
		ceph_del_rw_context(fi, &rw_ctx);
		dout("filemap_fault %p %llu~%zd drop cap refs %s ret %x\n",
			inode, off, (size_t)PAGE_SIZE,
				ceph_cap_string(got), ret);
	} else
		err = -EAGAIN;

	if (pinned_page)
		put_page(pinned_page);
	ceph_put_cap_refs(ci, got);

	if (err != -EAGAIN)
		goto out_restore;

	/* read inline data */
	if (off >= PAGE_SIZE) {
		/* does not support inline data > PAGE_SIZE */
		ret = VM_FAULT_SIGBUS;
	} else {
		struct address_space *mapping = inode->i_mapping;
		struct page *page = find_or_create_page(mapping, 0,
						mapping_gfp_constraint(mapping,
						~__GFP_FS));
		if (!page) {
			ret = VM_FAULT_OOM;
			goto out_inline;
		}
		err = __ceph_do_getattr(inode, page,
					 CEPH_STAT_CAP_INLINE_DATA, true);
		if (err < 0 || off >= i_size_read(inode)) {
			unlock_page(page);
			put_page(page);
			ret = vmf_error(err);
			goto out_inline;
		}
		if (err < PAGE_SIZE)
			zero_user_segment(page, err, PAGE_SIZE);
		else
			flush_dcache_page(page);
		SetPageUptodate(page);
		vmf->page = page;
		ret = VM_FAULT_MAJOR | VM_FAULT_LOCKED;
out_inline:
		dout("filemap_fault %p %llu~%zd read inline data ret %x\n",
		     inode, off, (size_t)PAGE_SIZE, ret);
	}
out_restore:
	ceph_restore_sigs(&oldset);
	if (err < 0)
		ret = vmf_error(err);

	return ret;
}