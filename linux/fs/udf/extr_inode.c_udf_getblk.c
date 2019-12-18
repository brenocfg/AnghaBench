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
typedef  int /*<<< orphan*/  udf_pblk_t ;
struct inode {TYPE_1__* i_sb; } ;
struct buffer_head {int b_blocknr; int /*<<< orphan*/  b_data; scalar_t__ b_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_blocksize; } ;

/* Variables and functions */
 scalar_t__ buffer_mapped (struct buffer_head*) ; 
 scalar_t__ buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,struct inode*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_getblk (TYPE_1__*,int) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int udf_get_block (struct inode*,int /*<<< orphan*/ ,struct buffer_head*,int) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static struct buffer_head *udf_getblk(struct inode *inode, udf_pblk_t block,
				      int create, int *err)
{
	struct buffer_head *bh;
	struct buffer_head dummy;

	dummy.b_state = 0;
	dummy.b_blocknr = -1000;
	*err = udf_get_block(inode, block, &dummy, create);
	if (!*err && buffer_mapped(&dummy)) {
		bh = sb_getblk(inode->i_sb, dummy.b_blocknr);
		if (buffer_new(&dummy)) {
			lock_buffer(bh);
			memset(bh->b_data, 0x00, inode->i_sb->s_blocksize);
			set_buffer_uptodate(bh);
			unlock_buffer(bh);
			mark_buffer_dirty_inode(bh, inode);
		}
		return bh;
	}

	return NULL;
}