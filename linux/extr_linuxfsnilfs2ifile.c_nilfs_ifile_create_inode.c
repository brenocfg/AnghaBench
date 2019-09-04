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
struct nilfs_palloc_req {struct buffer_head* pr_entry_bh; scalar_t__ pr_entry_nr; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_dirty (struct inode*) ; 
 int /*<<< orphan*/  nilfs_palloc_abort_alloc_entry (struct inode*,struct nilfs_palloc_req*) ; 
 int /*<<< orphan*/  nilfs_palloc_commit_alloc_entry (struct inode*,struct nilfs_palloc_req*) ; 
 int nilfs_palloc_get_entry_block (struct inode*,scalar_t__,int,struct buffer_head**) ; 
 int nilfs_palloc_prepare_alloc_entry (struct inode*,struct nilfs_palloc_req*) ; 

int nilfs_ifile_create_inode(struct inode *ifile, ino_t *out_ino,
			     struct buffer_head **out_bh)
{
	struct nilfs_palloc_req req;
	int ret;

	req.pr_entry_nr = 0;  /*
			       * 0 says find free inode from beginning
			       * of a group. dull code!!
			       */
	req.pr_entry_bh = NULL;

	ret = nilfs_palloc_prepare_alloc_entry(ifile, &req);
	if (!ret) {
		ret = nilfs_palloc_get_entry_block(ifile, req.pr_entry_nr, 1,
						   &req.pr_entry_bh);
		if (ret < 0)
			nilfs_palloc_abort_alloc_entry(ifile, &req);
	}
	if (ret < 0) {
		brelse(req.pr_entry_bh);
		return ret;
	}
	nilfs_palloc_commit_alloc_entry(ifile, &req);
	mark_buffer_dirty(req.pr_entry_bh);
	nilfs_mdt_mark_dirty(ifile);
	*out_ino = (ino_t)req.pr_entry_nr;
	*out_bh = req.pr_entry_bh;
	return 0;
}