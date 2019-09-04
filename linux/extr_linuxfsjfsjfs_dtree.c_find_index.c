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
typedef  int u32 ;
struct metapage {scalar_t__ data; } ;
struct jfs_inode_info {int next_index; struct dir_table_slot* i_dirtable; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dir_table_slot {int dummy; } ;
typedef  int s64 ;
struct TYPE_2__ {int l2nbperpage; } ;

/* Variables and functions */
 struct jfs_inode_info* JFS_IP (struct inode*) ; 
 TYPE_1__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int L2PSIZE ; 
 int PSIZE ; 
 scalar_t__ jfs_dirtable_inline (struct inode*) ; 
 int /*<<< orphan*/  jfs_err (char*) ; 
 int /*<<< orphan*/  jfs_warn (char*,...) ; 
 struct metapage* read_index_page (struct inode*,int) ; 
 int /*<<< orphan*/  release_metapage (struct metapage*) ; 

__attribute__((used)) static struct dir_table_slot *find_index(struct inode *ip, u32 index,
					 struct metapage ** mp, s64 *lblock)
{
	struct jfs_inode_info *jfs_ip = JFS_IP(ip);
	s64 blkno;
	s64 offset;
	int page_offset;
	struct dir_table_slot *slot;
	static int maxWarnings = 10;

	if (index < 2) {
		if (maxWarnings) {
			jfs_warn("find_entry called with index = %d", index);
			maxWarnings--;
		}
		return NULL;
	}

	if (index >= jfs_ip->next_index) {
		jfs_warn("find_entry called with index >= next_index");
		return NULL;
	}

	if (jfs_dirtable_inline(ip)) {
		/*
		 * Inline directory table
		 */
		*mp = NULL;
		slot = &jfs_ip->i_dirtable[index - 2];
	} else {
		offset = (index - 2) * sizeof(struct dir_table_slot);
		page_offset = offset & (PSIZE - 1);
		blkno = ((offset + 1) >> L2PSIZE) <<
		    JFS_SBI(ip->i_sb)->l2nbperpage;

		if (*mp && (*lblock != blkno)) {
			release_metapage(*mp);
			*mp = NULL;
		}
		if (!(*mp)) {
			*lblock = blkno;
			*mp = read_index_page(ip, blkno);
		}
		if (!(*mp)) {
			jfs_err("free_index: error reading directory table");
			return NULL;
		}

		slot =
		    (struct dir_table_slot *) ((char *) (*mp)->data +
					       page_offset);
	}
	return slot;
}