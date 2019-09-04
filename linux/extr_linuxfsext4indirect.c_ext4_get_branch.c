#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int ext4_lblk_t ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_7__ {int i_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ Indirect ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 TYPE_5__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  add_chain (TYPE_1__*,struct buffer_head*,int) ; 
 scalar_t__ bh_submit_read (struct buffer_head*) ; 
 int /*<<< orphan*/  bh_uptodate_or_lock (struct buffer_head*) ; 
 scalar_t__ ext4_check_indirect_blockref (struct inode*,struct buffer_head*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 struct buffer_head* sb_getblk (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static Indirect *ext4_get_branch(struct inode *inode, int depth,
				 ext4_lblk_t  *offsets,
				 Indirect chain[4], int *err)
{
	struct super_block *sb = inode->i_sb;
	Indirect *p = chain;
	struct buffer_head *bh;
	int ret = -EIO;

	*err = 0;
	/* i_data is not going away, no lock needed */
	add_chain(chain, NULL, EXT4_I(inode)->i_data + *offsets);
	if (!p->key)
		goto no_block;
	while (--depth) {
		bh = sb_getblk(sb, le32_to_cpu(p->key));
		if (unlikely(!bh)) {
			ret = -ENOMEM;
			goto failure;
		}

		if (!bh_uptodate_or_lock(bh)) {
			if (bh_submit_read(bh) < 0) {
				put_bh(bh);
				goto failure;
			}
			/* validate block references */
			if (ext4_check_indirect_blockref(inode, bh)) {
				put_bh(bh);
				goto failure;
			}
		}

		add_chain(++p, bh, (__le32 *)bh->b_data + *++offsets);
		/* Reader: end */
		if (!p->key)
			goto no_block;
	}
	return NULL;

failure:
	*err = ret;
no_block:
	return p;
}