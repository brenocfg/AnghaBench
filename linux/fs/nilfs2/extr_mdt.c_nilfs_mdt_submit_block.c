#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mapping; } ;
struct buffer_head {int /*<<< orphan*/  b_page; int /*<<< orphan*/  b_end_io; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  scalar_t__ __u64 ;
struct TYPE_2__ {int /*<<< orphan*/  i_bmap; } ;

/* Variables and functions */
 int EBUSY ; 
 int EEXIST ; 
 int ENOMEM ; 
 TYPE_1__* NILFS_I (struct inode*) ; 
 int REQ_RAHEAD ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  end_buffer_read_sync ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nilfs_bmap_lookup (int /*<<< orphan*/ ,unsigned long,scalar_t__*) ; 
 struct buffer_head* nilfs_grab_buffer (struct inode*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  submit_bh (int,int,struct buffer_head*) ; 
 int /*<<< orphan*/  trace_nilfs2_mdt_submit_block (struct inode*,int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  trylock_buffer (struct buffer_head*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nilfs_mdt_submit_block(struct inode *inode, unsigned long blkoff,
		       int mode, int mode_flags, struct buffer_head **out_bh)
{
	struct buffer_head *bh;
	__u64 blknum = 0;
	int ret = -ENOMEM;

	bh = nilfs_grab_buffer(inode, inode->i_mapping, blkoff, 0);
	if (unlikely(!bh))
		goto failed;

	ret = -EEXIST; /* internal code */
	if (buffer_uptodate(bh))
		goto out;

	if (mode_flags & REQ_RAHEAD) {
		if (!trylock_buffer(bh)) {
			ret = -EBUSY;
			goto failed_bh;
		}
	} else /* mode == READ */
		lock_buffer(bh);

	if (buffer_uptodate(bh)) {
		unlock_buffer(bh);
		goto out;
	}

	ret = nilfs_bmap_lookup(NILFS_I(inode)->i_bmap, blkoff, &blknum);
	if (unlikely(ret)) {
		unlock_buffer(bh);
		goto failed_bh;
	}
	map_bh(bh, inode->i_sb, (sector_t)blknum);

	bh->b_end_io = end_buffer_read_sync;
	get_bh(bh);
	submit_bh(mode, mode_flags, bh);
	ret = 0;

	trace_nilfs2_mdt_submit_block(inode, inode->i_ino, blkoff, mode);
 out:
	get_bh(bh);
	*out_bh = bh;

 failed_bh:
	unlock_page(bh->b_page);
	put_page(bh->b_page);
	brelse(bh);
 failed:
	return ret;
}