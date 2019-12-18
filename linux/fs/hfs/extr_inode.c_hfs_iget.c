#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int dummy; } ;
struct inode {int i_state; } ;
struct hfs_iget_data {TYPE_3__* member_1; struct hfs_cat_key* member_0; } ;
struct hfs_cat_key {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  FlNum; } ;
struct TYPE_5__ {int /*<<< orphan*/  DirID; } ;
struct TYPE_7__ {int type; TYPE_2__ file; TYPE_1__ dir; } ;
typedef  TYPE_3__ hfs_cat_rec ;

/* Variables and functions */
#define  HFS_CDR_DIR 129 
#define  HFS_CDR_FIL 128 
 int I_NEW ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_read_inode ; 
 int /*<<< orphan*/  hfs_test_inode ; 
 struct inode* iget5_locked (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hfs_iget_data*) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *hfs_iget(struct super_block *sb, struct hfs_cat_key *key, hfs_cat_rec *rec)
{
	struct hfs_iget_data data = { key, rec };
	struct inode *inode;
	u32 cnid;

	switch (rec->type) {
	case HFS_CDR_DIR:
		cnid = be32_to_cpu(rec->dir.DirID);
		break;
	case HFS_CDR_FIL:
		cnid = be32_to_cpu(rec->file.FlNum);
		break;
	default:
		return NULL;
	}
	inode = iget5_locked(sb, cnid, hfs_test_inode, hfs_read_inode, &data);
	if (inode && (inode->i_state & I_NEW))
		unlock_new_inode(inode);
	return inode;
}