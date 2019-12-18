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
typedef  int /*<<< orphan*/  handle_t ;
typedef  int /*<<< orphan*/  ext4_lblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 struct buffer_head* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int REQ_META ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int REQ_PRIO ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 scalar_t__ ext4_buffer_uptodate (struct buffer_head*) ; 
 struct buffer_head* ext4_getblk (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ll_rw_block (int /*<<< orphan*/ ,int,int,struct buffer_head**) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

struct buffer_head *ext4_bread(handle_t *handle, struct inode *inode,
			       ext4_lblk_t block, int map_flags)
{
	struct buffer_head *bh;

	bh = ext4_getblk(handle, inode, block, map_flags);
	if (IS_ERR(bh))
		return bh;
	if (!bh || ext4_buffer_uptodate(bh))
		return bh;
	ll_rw_block(REQ_OP_READ, REQ_META | REQ_PRIO, 1, &bh);
	wait_on_buffer(bh);
	if (buffer_uptodate(bh))
		return bh;
	put_bh(bh);
	return ERR_PTR(-EIO);
}