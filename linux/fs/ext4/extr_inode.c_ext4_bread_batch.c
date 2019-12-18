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
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ ext4_lblk_t ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int PTR_ERR (struct buffer_head*) ; 
 int REQ_META ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int REQ_PRIO ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_buffer_uptodate (struct buffer_head*) ; 
 struct buffer_head* ext4_getblk (int /*<<< orphan*/ *,struct inode*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ll_rw_block (int /*<<< orphan*/ ,int,int,struct buffer_head**) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

int ext4_bread_batch(struct inode *inode, ext4_lblk_t block, int bh_count,
		     bool wait, struct buffer_head **bhs)
{
	int i, err;

	for (i = 0; i < bh_count; i++) {
		bhs[i] = ext4_getblk(NULL, inode, block + i, 0 /* map_flags */);
		if (IS_ERR(bhs[i])) {
			err = PTR_ERR(bhs[i]);
			bh_count = i;
			goto out_brelse;
		}
	}

	for (i = 0; i < bh_count; i++)
		/* Note that NULL bhs[i] is valid because of holes. */
		if (bhs[i] && !ext4_buffer_uptodate(bhs[i]))
			ll_rw_block(REQ_OP_READ, REQ_META | REQ_PRIO, 1,
				    &bhs[i]);

	if (!wait)
		return 0;

	for (i = 0; i < bh_count; i++)
		if (bhs[i])
			wait_on_buffer(bhs[i]);

	for (i = 0; i < bh_count; i++) {
		if (bhs[i] && !buffer_uptodate(bhs[i])) {
			err = -EIO;
			goto out_brelse;
		}
	}
	return 0;

out_brelse:
	for (i = 0; i < bh_count; i++) {
		brelse(bhs[i]);
		bhs[i] = NULL;
	}
	return err;
}