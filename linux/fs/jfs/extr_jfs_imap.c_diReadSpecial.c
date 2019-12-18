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
typedef  int uint ;
struct super_block {int dummy; } ;
struct metapage {scalar_t__ data; } ;
struct jfs_sb_info {int l2nbperpage; scalar_t__ ipaimap2; scalar_t__ ipaimap; void* inostamp; void* gengen; int /*<<< orphan*/  ait2; } ;
struct inode {int i_ino; int /*<<< orphan*/  i_flags; TYPE_1__* i_mapping; } ;
struct dinode {int /*<<< orphan*/  di_inostamp; int /*<<< orphan*/  di_gengen; } ;
typedef  int ino_t ;
struct TYPE_4__ {scalar_t__ ipimap; } ;
struct TYPE_3__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int AITBL_OFF ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int FILESYSTEM_I ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int INOSPEREXT ; 
 TYPE_2__* JFS_IP (struct inode*) ; 
 struct jfs_sb_info* JFS_SBI (struct super_block*) ; 
 int L2PSIZE ; 
 int /*<<< orphan*/  PSIZE ; 
 int /*<<< orphan*/  S_NOQUOTA ; 
 int addressPXD (int /*<<< orphan*/ *) ; 
 scalar_t__ copy_from_dinode (struct dinode*,struct inode*) ; 
 int /*<<< orphan*/  inode_fake_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  jfs_err (char*) ; 
 int /*<<< orphan*/  jfs_metapage_aops ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping_set_gfp_mask (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct inode* new_inode (struct super_block*) ; 
 struct metapage* read_metapage (struct inode*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_metapage (struct metapage*) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 

struct inode *diReadSpecial(struct super_block *sb, ino_t inum, int secondary)
{
	struct jfs_sb_info *sbi = JFS_SBI(sb);
	uint address;
	struct dinode *dp;
	struct inode *ip;
	struct metapage *mp;

	ip = new_inode(sb);
	if (ip == NULL) {
		jfs_err("diReadSpecial: new_inode returned NULL!");
		return ip;
	}

	if (secondary) {
		address = addressPXD(&sbi->ait2) >> sbi->l2nbperpage;
		JFS_IP(ip)->ipimap = sbi->ipaimap2;
	} else {
		address = AITBL_OFF >> L2PSIZE;
		JFS_IP(ip)->ipimap = sbi->ipaimap;
	}

	ASSERT(inum < INOSPEREXT);

	ip->i_ino = inum;

	address += inum >> 3;	/* 8 inodes per 4K page */

	/* read the page of fixed disk inode (AIT) in raw mode */
	mp = read_metapage(ip, address << sbi->l2nbperpage, PSIZE, 1);
	if (mp == NULL) {
		set_nlink(ip, 1);	/* Don't want iput() deleting it */
		iput(ip);
		return (NULL);
	}

	/* get the pointer to the disk inode of interest */
	dp = (struct dinode *) (mp->data);
	dp += inum % 8;		/* 8 inodes per 4K page */

	/* copy on-disk inode to in-memory inode */
	if ((copy_from_dinode(dp, ip)) != 0) {
		/* handle bad return by returning NULL for ip */
		set_nlink(ip, 1);	/* Don't want iput() deleting it */
		iput(ip);
		/* release the page */
		release_metapage(mp);
		return (NULL);

	}

	ip->i_mapping->a_ops = &jfs_metapage_aops;
	mapping_set_gfp_mask(ip->i_mapping, GFP_NOFS);

	/* Allocations to metadata inodes should not affect quotas */
	ip->i_flags |= S_NOQUOTA;

	if ((inum == FILESYSTEM_I) && (JFS_IP(ip)->ipimap == sbi->ipaimap)) {
		sbi->gengen = le32_to_cpu(dp->di_gengen);
		sbi->inostamp = le32_to_cpu(dp->di_inostamp);
	}

	/* release the page */
	release_metapage(mp);

	inode_fake_hash(ip);

	return (ip);
}