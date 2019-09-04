#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  d_new_name; int /*<<< orphan*/  d_old_name; int /*<<< orphan*/  new_parent_refn; int /*<<< orphan*/  old_parent_refn; } ;
struct TYPE_11__ {TYPE_2__ rename; } ;
struct TYPE_12__ {TYPE_3__ req; } ;
struct orangefs_kernel_op_s {TYPE_4__ upcall; } ;
struct inode {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_6__* d_inode; TYPE_5__ d_name; TYPE_1__* d_parent; } ;
struct TYPE_15__ {int /*<<< orphan*/  refn; scalar_t__ getattr_time; } ;
struct TYPE_14__ {int /*<<< orphan*/  i_ctime; } ;
struct TYPE_9__ {struct inode* d_inode; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GOSSIP_NAME_DEBUG ; 
 TYPE_8__* ORANGEFS_I (struct inode*) ; 
 scalar_t__ ORANGEFS_NAME_MAX ; 
 int /*<<< orphan*/  ORANGEFS_VFS_OP_RENAME ; 
 int /*<<< orphan*/  current_time (TYPE_6__*) ; 
 int /*<<< orphan*/  d_count (struct dentry*) ; 
 int /*<<< orphan*/  get_interruptible_flag (TYPE_6__*) ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ jiffies ; 
 struct orangefs_kernel_op_s* op_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op_release (struct orangefs_kernel_op_s*) ; 
 int service_operation (struct orangefs_kernel_op_s*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int orangefs_rename(struct inode *old_dir,
			struct dentry *old_dentry,
			struct inode *new_dir,
			struct dentry *new_dentry,
			unsigned int flags)
{
	struct orangefs_kernel_op_s *new_op;
	int ret;

	if (flags)
		return -EINVAL;

	gossip_debug(GOSSIP_NAME_DEBUG,
		     "orangefs_rename: called (%pd2 => %pd2) ct=%d\n",
		     old_dentry, new_dentry, d_count(new_dentry));

	ORANGEFS_I(new_dentry->d_parent->d_inode)->getattr_time = jiffies - 1;

	new_op = op_alloc(ORANGEFS_VFS_OP_RENAME);
	if (!new_op)
		return -EINVAL;

	new_op->upcall.req.rename.old_parent_refn = ORANGEFS_I(old_dir)->refn;
	new_op->upcall.req.rename.new_parent_refn = ORANGEFS_I(new_dir)->refn;

	strncpy(new_op->upcall.req.rename.d_old_name,
		old_dentry->d_name.name,
		ORANGEFS_NAME_MAX - 1);
	strncpy(new_op->upcall.req.rename.d_new_name,
		new_dentry->d_name.name,
		ORANGEFS_NAME_MAX - 1);

	ret = service_operation(new_op,
				"orangefs_rename",
				get_interruptible_flag(old_dentry->d_inode));

	gossip_debug(GOSSIP_NAME_DEBUG,
		     "orangefs_rename: got downcall status %d\n",
		     ret);

	if (new_dentry->d_inode)
		new_dentry->d_inode->i_ctime = current_time(new_dentry->d_inode);

	op_release(new_op);
	return ret;
}