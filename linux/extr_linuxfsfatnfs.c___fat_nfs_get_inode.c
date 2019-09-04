#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct msdos_dir_entry {int /*<<< orphan*/  name; } ;
struct inode {scalar_t__ i_generation; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  scalar_t__ sector_t ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  llu ;
struct TYPE_4__ {scalar_t__ nfs; } ;
struct TYPE_5__ {TYPE_1__ options; } ;

/* Variables and functions */
 scalar_t__ FAT_NFS_NOSTALE_RO ; 
 scalar_t__ IS_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 TYPE_2__* MSDOS_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct inode* fat_build_inode (struct super_block*,struct msdos_dir_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fat_get_blknr_offset (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 struct inode* fat_ilookup (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fat_msg (struct super_block*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct buffer_head* sb_bread (struct super_block*,scalar_t__) ; 

__attribute__((used)) static struct inode *__fat_nfs_get_inode(struct super_block *sb,
				       u64 ino, u32 generation, loff_t i_pos)
{
	struct inode *inode = fat_ilookup(sb, ino, i_pos);

	if (inode && generation && (inode->i_generation != generation)) {
		iput(inode);
		inode = NULL;
	}
	if (inode == NULL && MSDOS_SB(sb)->options.nfs == FAT_NFS_NOSTALE_RO) {
		struct buffer_head *bh = NULL;
		struct msdos_dir_entry *de ;
		sector_t blocknr;
		int offset;
		fat_get_blknr_offset(MSDOS_SB(sb), i_pos, &blocknr, &offset);
		bh = sb_bread(sb, blocknr);
		if (!bh) {
			fat_msg(sb, KERN_ERR,
				"unable to read block(%llu) for building NFS inode",
				(llu)blocknr);
			return inode;
		}
		de = (struct msdos_dir_entry *)bh->b_data;
		/* If a file is deleted on server and client is not updated
		 * yet, we must not build the inode upon a lookup call.
		 */
		if (IS_FREE(de[offset].name))
			inode = NULL;
		else
			inode = fat_build_inode(sb, &de[offset], i_pos);
		brelse(bh);
	}

	return inode;
}