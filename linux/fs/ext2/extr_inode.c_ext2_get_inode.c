#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct ext2_inode {int dummy; } ;
struct ext2_group_desc {int /*<<< orphan*/  bg_inode_table; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int ino_t ;
struct TYPE_4__ {TYPE_1__* s_es; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_inodes_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 struct ext2_inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int EXT2_BLOCK_SIZE (struct super_block*) ; 
 unsigned long EXT2_BLOCK_SIZE_BITS (struct super_block*) ; 
 int EXT2_FIRST_INO (struct super_block*) ; 
 int EXT2_INODES_PER_GROUP (struct super_block*) ; 
 int EXT2_INODE_SIZE (struct super_block*) ; 
 int EXT2_ROOT_INO ; 
 TYPE_2__* EXT2_SB (struct super_block*) ; 
 int /*<<< orphan*/  ext2_error (struct super_block*,char*,char*,unsigned long,...) ; 
 struct ext2_group_desc* ext2_get_group_desc (struct super_block*,unsigned long,int /*<<< orphan*/ *) ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_bread (struct super_block*,unsigned long) ; 

__attribute__((used)) static struct ext2_inode *ext2_get_inode(struct super_block *sb, ino_t ino,
					struct buffer_head **p)
{
	struct buffer_head * bh;
	unsigned long block_group;
	unsigned long block;
	unsigned long offset;
	struct ext2_group_desc * gdp;

	*p = NULL;
	if ((ino != EXT2_ROOT_INO && ino < EXT2_FIRST_INO(sb)) ||
	    ino > le32_to_cpu(EXT2_SB(sb)->s_es->s_inodes_count))
		goto Einval;

	block_group = (ino - 1) / EXT2_INODES_PER_GROUP(sb);
	gdp = ext2_get_group_desc(sb, block_group, NULL);
	if (!gdp)
		goto Egdp;
	/*
	 * Figure out the offset within the block group inode table
	 */
	offset = ((ino - 1) % EXT2_INODES_PER_GROUP(sb)) * EXT2_INODE_SIZE(sb);
	block = le32_to_cpu(gdp->bg_inode_table) +
		(offset >> EXT2_BLOCK_SIZE_BITS(sb));
	if (!(bh = sb_bread(sb, block)))
		goto Eio;

	*p = bh;
	offset &= (EXT2_BLOCK_SIZE(sb) - 1);
	return (struct ext2_inode *) (bh->b_data + offset);

Einval:
	ext2_error(sb, "ext2_get_inode", "bad inode number: %lu",
		   (unsigned long) ino);
	return ERR_PTR(-EINVAL);
Eio:
	ext2_error(sb, "ext2_get_inode",
		   "unable to read inode block - inode=%lu, block=%lu",
		   (unsigned long) ino, block);
Egdp:
	return ERR_PTR(-EIO);
}