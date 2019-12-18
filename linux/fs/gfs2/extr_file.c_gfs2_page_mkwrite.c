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
typedef  int /*<<< orphan*/  vm_fault_t ;
typedef  int /*<<< orphan*/  u64 ;
struct vm_fault {TYPE_1__* vma; struct page* page; } ;
struct page {scalar_t__ mapping; unsigned long index; } ;
struct inode {scalar_t__ i_mapping; int /*<<< orphan*/  i_sb; } ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_inode {int /*<<< orphan*/  i_flags; TYPE_2__* i_gl; } ;
struct gfs2_holder {int dummy; } ;
struct gfs2_alloc_parms {unsigned int target; int /*<<< orphan*/  aflags; } ;
typedef  int loff_t ;
struct TYPE_4__ {int /*<<< orphan*/  gl_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  vm_file; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  GIF_SW_PAGED ; 
 int /*<<< orphan*/  GLF_DIRTY ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 unsigned int RES_DINODE ; 
 scalar_t__ RES_QUOTA ; 
 scalar_t__ RES_STATFS ; 
 int /*<<< orphan*/  block_page_mkwrite_return (int) ; 
 struct inode* file_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_update_time (int /*<<< orphan*/ ) ; 
 int gfs2_allocate_page_backing (struct page*) ; 
 int /*<<< orphan*/  gfs2_glock_dq (struct gfs2_holder*) ; 
 int gfs2_glock_nq (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_uninit (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_inplace_release (struct gfs2_inode*) ; 
 int gfs2_inplace_reserve (struct gfs2_inode*,struct gfs2_alloc_parms*) ; 
 scalar_t__ gfs2_is_jdata (struct gfs2_inode*) ; 
 scalar_t__ gfs2_is_stuffed (struct gfs2_inode*) ; 
 int gfs2_quota_lock_check (struct gfs2_inode*,struct gfs2_alloc_parms*) ; 
 int /*<<< orphan*/  gfs2_quota_unlock (struct gfs2_inode*) ; 
 scalar_t__ gfs2_rg_blocks (struct gfs2_inode*,unsigned int) ; 
 int gfs2_rindex_update (struct gfs2_sbd*) ; 
 int gfs2_rsqa_alloc (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_size_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int gfs2_unstuff_dinode (struct gfs2_inode*,struct page*) ; 
 int /*<<< orphan*/  gfs2_write_alloc_required (struct gfs2_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_write_calc_reserv (struct gfs2_inode*,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  page_offset (struct page*) ; 
 int /*<<< orphan*/  sb_end_pagefault (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_pagefault (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_for_stable_page (struct page*) ; 

__attribute__((used)) static vm_fault_t gfs2_page_mkwrite(struct vm_fault *vmf)
{
	struct page *page = vmf->page;
	struct inode *inode = file_inode(vmf->vma->vm_file);
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct gfs2_alloc_parms ap = { .aflags = 0, };
	unsigned long last_index;
	u64 pos = page_offset(page);
	unsigned int data_blocks, ind_blocks, rblocks;
	struct gfs2_holder gh;
	loff_t size;
	int ret;

	sb_start_pagefault(inode->i_sb);

	ret = gfs2_rsqa_alloc(ip);
	if (ret)
		goto out;

	gfs2_size_hint(vmf->vma->vm_file, pos, PAGE_SIZE);

	gfs2_holder_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &gh);
	ret = gfs2_glock_nq(&gh);
	if (ret)
		goto out_uninit;

	/* Update file times before taking page lock */
	file_update_time(vmf->vma->vm_file);

	set_bit(GLF_DIRTY, &ip->i_gl->gl_flags);
	set_bit(GIF_SW_PAGED, &ip->i_flags);

	if (!gfs2_write_alloc_required(ip, pos, PAGE_SIZE)) {
		lock_page(page);
		if (!PageUptodate(page) || page->mapping != inode->i_mapping) {
			ret = -EAGAIN;
			unlock_page(page);
		}
		goto out_unlock;
	}

	ret = gfs2_rindex_update(sdp);
	if (ret)
		goto out_unlock;

	gfs2_write_calc_reserv(ip, PAGE_SIZE, &data_blocks, &ind_blocks);
	ap.target = data_blocks + ind_blocks;
	ret = gfs2_quota_lock_check(ip, &ap);
	if (ret)
		goto out_unlock;
	ret = gfs2_inplace_reserve(ip, &ap);
	if (ret)
		goto out_quota_unlock;

	rblocks = RES_DINODE + ind_blocks;
	if (gfs2_is_jdata(ip))
		rblocks += data_blocks ? data_blocks : 1;
	if (ind_blocks || data_blocks) {
		rblocks += RES_STATFS + RES_QUOTA;
		rblocks += gfs2_rg_blocks(ip, data_blocks + ind_blocks);
	}
	ret = gfs2_trans_begin(sdp, rblocks, 0);
	if (ret)
		goto out_trans_fail;

	lock_page(page);
	ret = -EINVAL;
	size = i_size_read(inode);
	last_index = (size - 1) >> PAGE_SHIFT;
	/* Check page index against inode size */
	if (size == 0 || (page->index > last_index))
		goto out_trans_end;

	ret = -EAGAIN;
	/* If truncated, we must retry the operation, we may have raced
	 * with the glock demotion code.
	 */
	if (!PageUptodate(page) || page->mapping != inode->i_mapping)
		goto out_trans_end;

	/* Unstuff, if required, and allocate backing blocks for page */
	ret = 0;
	if (gfs2_is_stuffed(ip))
		ret = gfs2_unstuff_dinode(ip, page);
	if (ret == 0)
		ret = gfs2_allocate_page_backing(page);

out_trans_end:
	if (ret)
		unlock_page(page);
	gfs2_trans_end(sdp);
out_trans_fail:
	gfs2_inplace_release(ip);
out_quota_unlock:
	gfs2_quota_unlock(ip);
out_unlock:
	gfs2_glock_dq(&gh);
out_uninit:
	gfs2_holder_uninit(&gh);
	if (ret == 0) {
		set_page_dirty(page);
		wait_for_stable_page(page);
	}
out:
	sb_end_pagefault(inode->i_sb);
	return block_page_mkwrite_return(ret);
}