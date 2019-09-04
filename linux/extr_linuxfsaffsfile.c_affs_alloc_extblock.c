#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct inode {scalar_t__ i_ino; struct super_block* i_sb; } ;
struct buffer_head {int /*<<< orphan*/  b_blocknr; } ;
struct TYPE_6__ {void* key; void* ptype; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_extcnt; } ;
struct TYPE_4__ {void* extension; void* parent; void* stype; } ;

/* Variables and functions */
 TYPE_3__* AFFS_HEAD (struct buffer_head*) ; 
 TYPE_2__* AFFS_I (struct inode*) ; 
 TYPE_1__* AFFS_TAIL (struct super_block*,struct buffer_head*) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOSPC ; 
 struct buffer_head* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ ST_FILE ; 
 scalar_t__ T_LIST ; 
 int /*<<< orphan*/  affs_adjust_checksum (struct buffer_head*,scalar_t__) ; 
 scalar_t__ affs_alloc_block (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  affs_fix_checksum (struct super_block*,struct buffer_head*) ; 
 int /*<<< orphan*/  affs_free_block (struct super_block*,scalar_t__) ; 
 struct buffer_head* affs_getzeroblk (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  affs_warning (struct super_block*,char*,char*,scalar_t__) ; 
 scalar_t__ be32_to_cpu (void*) ; 
 void* cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 

__attribute__((used)) static struct buffer_head *
affs_alloc_extblock(struct inode *inode, struct buffer_head *bh, u32 ext)
{
	struct super_block *sb = inode->i_sb;
	struct buffer_head *new_bh;
	u32 blocknr, tmp;

	blocknr = affs_alloc_block(inode, bh->b_blocknr);
	if (!blocknr)
		return ERR_PTR(-ENOSPC);

	new_bh = affs_getzeroblk(sb, blocknr);
	if (!new_bh) {
		affs_free_block(sb, blocknr);
		return ERR_PTR(-EIO);
	}

	AFFS_HEAD(new_bh)->ptype = cpu_to_be32(T_LIST);
	AFFS_HEAD(new_bh)->key = cpu_to_be32(blocknr);
	AFFS_TAIL(sb, new_bh)->stype = cpu_to_be32(ST_FILE);
	AFFS_TAIL(sb, new_bh)->parent = cpu_to_be32(inode->i_ino);
	affs_fix_checksum(sb, new_bh);

	mark_buffer_dirty_inode(new_bh, inode);

	tmp = be32_to_cpu(AFFS_TAIL(sb, bh)->extension);
	if (tmp)
		affs_warning(sb, "alloc_ext", "previous extension set (%x)", tmp);
	AFFS_TAIL(sb, bh)->extension = cpu_to_be32(blocknr);
	affs_adjust_checksum(bh, blocknr - tmp);
	mark_buffer_dirty_inode(bh, inode);

	AFFS_I(inode)->i_extcnt++;
	mark_inode_dirty(inode);

	return new_bh;
}