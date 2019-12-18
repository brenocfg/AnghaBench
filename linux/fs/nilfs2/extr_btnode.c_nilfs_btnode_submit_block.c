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
struct the_nilfs {int /*<<< orphan*/  ns_dat; } ;
struct page {int dummy; } ;
struct inode {scalar_t__ i_ino; TYPE_1__* i_sb; } ;
struct buffer_head {void* b_blocknr; int /*<<< orphan*/  b_end_io; int /*<<< orphan*/  b_bdev; struct page* b_page; } ;
struct address_space {int dummy; } ;
typedef  scalar_t__ sector_t ;
typedef  void* __u64 ;
struct TYPE_2__ {int /*<<< orphan*/  s_bdev; struct the_nilfs* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BH_NILFS_Node ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int EEXIST ; 
 int ENOMEM ; 
 struct inode* NILFS_BTNC_I (struct address_space*) ; 
 scalar_t__ NILFS_DAT_INO ; 
 int REQ_RAHEAD ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  end_buffer_read_sync ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int nilfs_dat_translate (int /*<<< orphan*/ ,void*,scalar_t__*) ; 
 struct buffer_head* nilfs_grab_buffer (struct inode*,struct address_space*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  submit_bh (int,int,struct buffer_head*) ; 
 int /*<<< orphan*/  trylock_buffer (struct buffer_head*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int nilfs_btnode_submit_block(struct address_space *btnc, __u64 blocknr,
			      sector_t pblocknr, int mode, int mode_flags,
			      struct buffer_head **pbh, sector_t *submit_ptr)
{
	struct buffer_head *bh;
	struct inode *inode = NILFS_BTNC_I(btnc);
	struct page *page;
	int err;

	bh = nilfs_grab_buffer(inode, btnc, blocknr, BIT(BH_NILFS_Node));
	if (unlikely(!bh))
		return -ENOMEM;

	err = -EEXIST; /* internal code */
	page = bh->b_page;

	if (buffer_uptodate(bh) || buffer_dirty(bh))
		goto found;

	if (pblocknr == 0) {
		pblocknr = blocknr;
		if (inode->i_ino != NILFS_DAT_INO) {
			struct the_nilfs *nilfs = inode->i_sb->s_fs_info;

			/* blocknr is a virtual block number */
			err = nilfs_dat_translate(nilfs->ns_dat, blocknr,
						  &pblocknr);
			if (unlikely(err)) {
				brelse(bh);
				goto out_locked;
			}
		}
	}

	if (mode_flags & REQ_RAHEAD) {
		if (pblocknr != *submit_ptr + 1 || !trylock_buffer(bh)) {
			err = -EBUSY; /* internal code */
			brelse(bh);
			goto out_locked;
		}
	} else { /* mode == READ */
		lock_buffer(bh);
	}
	if (buffer_uptodate(bh)) {
		unlock_buffer(bh);
		err = -EEXIST; /* internal code */
		goto found;
	}
	set_buffer_mapped(bh);
	bh->b_bdev = inode->i_sb->s_bdev;
	bh->b_blocknr = pblocknr; /* set block address for read */
	bh->b_end_io = end_buffer_read_sync;
	get_bh(bh);
	submit_bh(mode, mode_flags, bh);
	bh->b_blocknr = blocknr; /* set back to the given block address */
	*submit_ptr = pblocknr;
	err = 0;
found:
	*pbh = bh;

out_locked:
	unlock_page(page);
	put_page(page);
	return err;
}