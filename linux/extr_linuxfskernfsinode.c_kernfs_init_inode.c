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
struct TYPE_6__ {int /*<<< orphan*/  size; } ;
struct TYPE_5__ {int /*<<< orphan*/  generation; } ;
struct kernfs_node {int flags; TYPE_3__ attr; int /*<<< orphan*/  mode; TYPE_2__ id; } ;
struct inode {int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_generation; TYPE_1__* i_mapping; struct kernfs_node* i_private; } ;
struct TYPE_4__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  KERNFS_DIR 130 
 int KERNFS_EMPTY_DIR ; 
#define  KERNFS_FILE 129 
#define  KERNFS_LINK 128 
 int /*<<< orphan*/  kernfs_aops ; 
 int /*<<< orphan*/  kernfs_dir_fops ; 
 int /*<<< orphan*/  kernfs_dir_iops ; 
 int /*<<< orphan*/  kernfs_file_fops ; 
 int /*<<< orphan*/  kernfs_get (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_iops ; 
 int /*<<< orphan*/  kernfs_refresh_inode (struct kernfs_node*,struct inode*) ; 
 int /*<<< orphan*/  kernfs_symlink_iops ; 
 int kernfs_type (struct kernfs_node*) ; 
 int /*<<< orphan*/  make_empty_dir_inode (struct inode*) ; 
 int /*<<< orphan*/  set_default_inode_attr (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static void kernfs_init_inode(struct kernfs_node *kn, struct inode *inode)
{
	kernfs_get(kn);
	inode->i_private = kn;
	inode->i_mapping->a_ops = &kernfs_aops;
	inode->i_op = &kernfs_iops;
	inode->i_generation = kn->id.generation;

	set_default_inode_attr(inode, kn->mode);
	kernfs_refresh_inode(kn, inode);

	/* initialize inode according to type */
	switch (kernfs_type(kn)) {
	case KERNFS_DIR:
		inode->i_op = &kernfs_dir_iops;
		inode->i_fop = &kernfs_dir_fops;
		if (kn->flags & KERNFS_EMPTY_DIR)
			make_empty_dir_inode(inode);
		break;
	case KERNFS_FILE:
		inode->i_size = kn->attr.size;
		inode->i_fop = &kernfs_file_fops;
		break;
	case KERNFS_LINK:
		inode->i_op = &kernfs_symlink_iops;
		break;
	default:
		BUG();
	}

	unlock_new_inode(inode);
}