#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nilfs_palloc_req {TYPE_1__* pr_entry_bh; int /*<<< orphan*/  pr_entry_nr; } ;
struct nilfs_inode {scalar_t__ i_flags; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_5__ {int /*<<< orphan*/  b_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (TYPE_1__*) ; 
 void* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (TYPE_1__*) ; 
 int /*<<< orphan*/  nilfs_palloc_abort_free_entry (struct inode*,struct nilfs_palloc_req*) ; 
 struct nilfs_inode* nilfs_palloc_block_get_entry (struct inode*,int /*<<< orphan*/ ,TYPE_1__*,void*) ; 
 int /*<<< orphan*/  nilfs_palloc_commit_free_entry (struct inode*,struct nilfs_palloc_req*) ; 
 int nilfs_palloc_get_entry_block (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int nilfs_palloc_prepare_free_entry (struct inode*,struct nilfs_palloc_req*) ; 

int nilfs_ifile_delete_inode(struct inode *ifile, ino_t ino)
{
	struct nilfs_palloc_req req = {
		.pr_entry_nr = ino, .pr_entry_bh = NULL
	};
	struct nilfs_inode *raw_inode;
	void *kaddr;
	int ret;

	ret = nilfs_palloc_prepare_free_entry(ifile, &req);
	if (!ret) {
		ret = nilfs_palloc_get_entry_block(ifile, req.pr_entry_nr, 0,
						   &req.pr_entry_bh);
		if (ret < 0)
			nilfs_palloc_abort_free_entry(ifile, &req);
	}
	if (ret < 0) {
		brelse(req.pr_entry_bh);
		return ret;
	}

	kaddr = kmap_atomic(req.pr_entry_bh->b_page);
	raw_inode = nilfs_palloc_block_get_entry(ifile, req.pr_entry_nr,
						 req.pr_entry_bh, kaddr);
	raw_inode->i_flags = 0;
	kunmap_atomic(kaddr);

	mark_buffer_dirty(req.pr_entry_bh);
	brelse(req.pr_entry_bh);

	nilfs_palloc_commit_free_entry(ifile, &req);

	return 0;
}