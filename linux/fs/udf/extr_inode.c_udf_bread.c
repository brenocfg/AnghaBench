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
typedef  int /*<<< orphan*/  udf_pblk_t ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  REQ_OP_READ ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  ll_rw_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct buffer_head**) ; 
 struct buffer_head* udf_getblk (struct inode*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

struct buffer_head *udf_bread(struct inode *inode, udf_pblk_t block,
			      int create, int *err)
{
	struct buffer_head *bh = NULL;

	bh = udf_getblk(inode, block, create, err);
	if (!bh)
		return NULL;

	if (buffer_uptodate(bh))
		return bh;

	ll_rw_block(REQ_OP_READ, 0, 1, &bh);

	wait_on_buffer(bh);
	if (buffer_uptodate(bh))
		return bh;

	brelse(bh);
	*err = -EIO;
	return NULL;
}