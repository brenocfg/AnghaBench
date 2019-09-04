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
struct inode {int i_ino; TYPE_1__* i_mapping; int /*<<< orphan*/  i_sb; } ;
struct hfsplus_vh {int /*<<< orphan*/  attr_file; int /*<<< orphan*/  start_file; int /*<<< orphan*/  alloc_file; int /*<<< orphan*/  cat_file; int /*<<< orphan*/  ext_file; } ;
struct TYPE_4__ {struct hfsplus_vh* s_vhdr; } ;
struct TYPE_3__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int EIO ; 
#define  HFSPLUS_ALLOC_CNID 132 
#define  HFSPLUS_ATTR_CNID 131 
#define  HFSPLUS_CAT_CNID 130 
#define  HFSPLUS_EXT_CNID 129 
 TYPE_2__* HFSPLUS_SB (int /*<<< orphan*/ ) ; 
#define  HFSPLUS_START_CNID 128 
 int /*<<< orphan*/  hfsplus_aops ; 
 int /*<<< orphan*/  hfsplus_btree_aops ; 
 int /*<<< orphan*/  hfsplus_inode_read_fork (struct inode*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hfsplus_system_read_inode(struct inode *inode)
{
	struct hfsplus_vh *vhdr = HFSPLUS_SB(inode->i_sb)->s_vhdr;

	switch (inode->i_ino) {
	case HFSPLUS_EXT_CNID:
		hfsplus_inode_read_fork(inode, &vhdr->ext_file);
		inode->i_mapping->a_ops = &hfsplus_btree_aops;
		break;
	case HFSPLUS_CAT_CNID:
		hfsplus_inode_read_fork(inode, &vhdr->cat_file);
		inode->i_mapping->a_ops = &hfsplus_btree_aops;
		break;
	case HFSPLUS_ALLOC_CNID:
		hfsplus_inode_read_fork(inode, &vhdr->alloc_file);
		inode->i_mapping->a_ops = &hfsplus_aops;
		break;
	case HFSPLUS_START_CNID:
		hfsplus_inode_read_fork(inode, &vhdr->start_file);
		break;
	case HFSPLUS_ATTR_CNID:
		hfsplus_inode_read_fork(inode, &vhdr->attr_file);
		inode->i_mapping->a_ops = &hfsplus_btree_aops;
		break;
	default:
		return -EIO;
	}

	return 0;
}