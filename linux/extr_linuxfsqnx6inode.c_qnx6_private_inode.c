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
struct super_block {int dummy; } ;
struct qnx6_sb_info {int dummy; } ;
struct qnx6_root_node {int /*<<< orphan*/  levels; int /*<<< orphan*/  ptr; int /*<<< orphan*/  size; } ;
struct qnx6_inode_info {int /*<<< orphan*/  di_filelevels; int /*<<< orphan*/  di_block_ptr; } ;
struct inode {int i_mode; TYPE_1__* i_mapping; int /*<<< orphan*/  i_size; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 struct qnx6_inode_info* QNX6_I (struct inode*) ; 
 struct qnx6_sb_info* QNX6_SB (struct super_block*) ; 
 int S_IFREG ; 
 int S_IRUSR ; 
 int /*<<< orphan*/  fs64_to_cpu (struct qnx6_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  qnx6_aops ; 

__attribute__((used)) static struct inode *qnx6_private_inode(struct super_block *s,
					struct qnx6_root_node *p)
{
	struct inode *inode = new_inode(s);
	if (inode) {
		struct qnx6_inode_info *ei = QNX6_I(inode);
		struct qnx6_sb_info *sbi = QNX6_SB(s);
		inode->i_size = fs64_to_cpu(sbi, p->size);
		memcpy(ei->di_block_ptr, p->ptr, sizeof(p->ptr));
		ei->di_filelevels = p->levels;
		inode->i_mode = S_IFREG | S_IRUSR; /* probably wrong */
		inode->i_mapping->a_ops = &qnx6_aops;
	}
	return inode;
}