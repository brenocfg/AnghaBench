#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct hpfs_inode_info {unsigned int i_file_sec; unsigned int i_disk_sec; unsigned int i_n_secs; } ;
struct buffer_head {int dummy; } ;
struct TYPE_7__ {TYPE_2__* external; TYPE_1__* internal; } ;
struct bplus_header {int n_used_nodes; TYPE_3__ u; } ;
struct anode {struct bplus_header btree; } ;
typedef  int secno ;
typedef  int anode_secno ;
struct TYPE_8__ {scalar_t__ sb_chk; } ;
struct TYPE_6__ {int /*<<< orphan*/  length; int /*<<< orphan*/  disk_secno; int /*<<< orphan*/  file_secno; } ;
struct TYPE_5__ {int /*<<< orphan*/  down; int /*<<< orphan*/  file_secno; } ;

/* Variables and functions */
 scalar_t__ bp_internal (struct bplus_header*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ hpfs_chk_sectors (struct super_block*,int,int,char*) ; 
 int /*<<< orphan*/  hpfs_error (struct super_block*,char*,unsigned int,int) ; 
 struct hpfs_inode_info* hpfs_i (struct inode*) ; 
 struct anode* hpfs_map_anode (struct super_block*,int,struct buffer_head**) ; 
 TYPE_4__* hpfs_sb (struct super_block*) ; 
 scalar_t__ hpfs_stop_cycles (struct super_block*,int,int*,int*,char*) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 

secno hpfs_bplus_lookup(struct super_block *s, struct inode *inode,
		   struct bplus_header *btree, unsigned sec,
		   struct buffer_head *bh)
{
	anode_secno a = -1;
	struct anode *anode;
	int i;
	int c1, c2 = 0;
	go_down:
	if (hpfs_sb(s)->sb_chk) if (hpfs_stop_cycles(s, a, &c1, &c2, "hpfs_bplus_lookup")) return -1;
	if (bp_internal(btree)) {
		for (i = 0; i < btree->n_used_nodes; i++)
			if (le32_to_cpu(btree->u.internal[i].file_secno) > sec) {
				a = le32_to_cpu(btree->u.internal[i].down);
				brelse(bh);
				if (!(anode = hpfs_map_anode(s, a, &bh))) return -1;
				btree = &anode->btree;
				goto go_down;
			}
		hpfs_error(s, "sector %08x not found in internal anode %08x", sec, a);
		brelse(bh);
		return -1;
	}
	for (i = 0; i < btree->n_used_nodes; i++)
		if (le32_to_cpu(btree->u.external[i].file_secno) <= sec &&
		    le32_to_cpu(btree->u.external[i].file_secno) + le32_to_cpu(btree->u.external[i].length) > sec) {
			a = le32_to_cpu(btree->u.external[i].disk_secno) + sec - le32_to_cpu(btree->u.external[i].file_secno);
			if (hpfs_sb(s)->sb_chk) if (hpfs_chk_sectors(s, a, 1, "data")) {
				brelse(bh);
				return -1;
			}
			if (inode) {
				struct hpfs_inode_info *hpfs_inode = hpfs_i(inode);
				hpfs_inode->i_file_sec = le32_to_cpu(btree->u.external[i].file_secno);
				hpfs_inode->i_disk_sec = le32_to_cpu(btree->u.external[i].disk_secno);
				hpfs_inode->i_n_secs = le32_to_cpu(btree->u.external[i].length);
			}
			brelse(bh);
			return a;
		}
	hpfs_error(s, "sector %08x not found in external anode %08x", sec, a);
	brelse(bh);
	return -1;
}