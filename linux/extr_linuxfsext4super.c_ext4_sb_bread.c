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
struct super_block {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct buffer_head* ERR_PTR (int /*<<< orphan*/ ) ; 
 int REQ_META ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  ll_rw_block (int /*<<< orphan*/ ,int,int,struct buffer_head**) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 struct buffer_head* sb_getblk (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

struct buffer_head *
ext4_sb_bread(struct super_block *sb, sector_t block, int op_flags)
{
	struct buffer_head *bh = sb_getblk(sb, block);

	if (bh == NULL)
		return ERR_PTR(-ENOMEM);
	if (buffer_uptodate(bh))
		return bh;
	ll_rw_block(REQ_OP_READ, REQ_META | op_flags, 1, &bh);
	wait_on_buffer(bh);
	if (buffer_uptodate(bh))
		return bh;
	put_bh(bh);
	return ERR_PTR(-EIO);
}