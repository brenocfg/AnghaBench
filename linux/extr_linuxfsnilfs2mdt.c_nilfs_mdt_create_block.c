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
struct super_block {int /*<<< orphan*/  s_bdev; } ;
struct nilfs_transaction_info {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; struct super_block* i_sb; } ;
struct buffer_head {int /*<<< orphan*/  b_page; int /*<<< orphan*/  b_bdev; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 scalar_t__ likely (int) ; 
 struct buffer_head* nilfs_grab_buffer (struct inode*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int nilfs_mdt_insert_new_block (struct inode*,unsigned long,struct buffer_head*,void (*) (struct inode*,struct buffer_head*,void*)) ; 
 int /*<<< orphan*/  nilfs_transaction_abort (struct super_block*) ; 
 int /*<<< orphan*/  nilfs_transaction_begin (struct super_block*,struct nilfs_transaction_info*,int /*<<< orphan*/ ) ; 
 int nilfs_transaction_commit (struct super_block*) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

__attribute__((used)) static int nilfs_mdt_create_block(struct inode *inode, unsigned long block,
				  struct buffer_head **out_bh,
				  void (*init_block)(struct inode *,
						     struct buffer_head *,
						     void *))
{
	struct super_block *sb = inode->i_sb;
	struct nilfs_transaction_info ti;
	struct buffer_head *bh;
	int err;

	nilfs_transaction_begin(sb, &ti, 0);

	err = -ENOMEM;
	bh = nilfs_grab_buffer(inode, inode->i_mapping, block, 0);
	if (unlikely(!bh))
		goto failed_unlock;

	err = -EEXIST;
	if (buffer_uptodate(bh))
		goto failed_bh;

	wait_on_buffer(bh);
	if (buffer_uptodate(bh))
		goto failed_bh;

	bh->b_bdev = sb->s_bdev;
	err = nilfs_mdt_insert_new_block(inode, block, bh, init_block);
	if (likely(!err)) {
		get_bh(bh);
		*out_bh = bh;
	}

 failed_bh:
	unlock_page(bh->b_page);
	put_page(bh->b_page);
	brelse(bh);

 failed_unlock:
	if (likely(!err))
		err = nilfs_transaction_commit(sb);
	else
		nilfs_transaction_abort(sb);

	return err;
}