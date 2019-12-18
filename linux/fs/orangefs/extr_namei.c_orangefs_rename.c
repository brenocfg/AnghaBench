#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  d_new_name; int /*<<< orphan*/  d_old_name; int /*<<< orphan*/  new_parent_refn; int /*<<< orphan*/  old_parent_refn; } ;
struct TYPE_7__ {TYPE_1__ rename; } ;
struct TYPE_8__ {TYPE_2__ req; } ;
struct orangefs_kernel_op_s {TYPE_3__ upcall; } ;
struct inode {void* i_ctime; } ;
struct iattr {int ia_valid; void* ia_ctime; void* ia_mtime; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct dentry {struct inode* d_inode; TYPE_4__ d_name; } ;
struct TYPE_10__ {int /*<<< orphan*/  refn; } ;

/* Variables and functions */
 int ATTR_CTIME ; 
 int ATTR_MTIME ; 
 int EINVAL ; 
 int /*<<< orphan*/  GOSSIP_NAME_DEBUG ; 
 TYPE_5__* ORANGEFS_I (struct inode*) ; 
 scalar_t__ ORANGEFS_NAME_MAX ; 
 int /*<<< orphan*/  ORANGEFS_VFS_OP_RENAME ; 
 int /*<<< orphan*/  __orangefs_setattr (struct inode*,struct iattr*) ; 
 void* current_time (struct inode*) ; 
 int /*<<< orphan*/  d_count (struct dentry*) ; 
 int /*<<< orphan*/  get_interruptible_flag (struct inode*) ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (struct iattr*,int /*<<< orphan*/ ,int) ; 
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
	struct iattr iattr;
	int ret;

	if (flags)
		return -EINVAL;

	gossip_debug(GOSSIP_NAME_DEBUG,
		     "orangefs_rename: called (%pd2 => %pd2) ct=%d\n",
		     old_dentry, new_dentry, d_count(new_dentry));

	memset(&iattr, 0, sizeof iattr);
	iattr.ia_valid |= ATTR_MTIME | ATTR_CTIME;
	iattr.ia_mtime = iattr.ia_ctime = current_time(new_dir);
	__orangefs_setattr(new_dir, &iattr);

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