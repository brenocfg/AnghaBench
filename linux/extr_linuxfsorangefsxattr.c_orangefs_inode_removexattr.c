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
struct TYPE_4__ {scalar_t__ key_sz; scalar_t__ key; int /*<<< orphan*/  refn; } ;
struct TYPE_5__ {TYPE_1__ removexattr; } ;
struct TYPE_6__ {TYPE_2__ req; } ;
struct orangefs_kernel_op_s {TYPE_3__ upcall; } ;
struct orangefs_inode_s {int /*<<< orphan*/  xattr_sem; int /*<<< orphan*/  refn; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GOSSIP_XATTR_DEBUG ; 
 struct orangefs_inode_s* ORANGEFS_I (struct inode*) ; 
 scalar_t__ ORANGEFS_MAX_XATTR_NAMELEN ; 
 int /*<<< orphan*/  ORANGEFS_VFS_OP_REMOVEXATTR ; 
 int XATTR_REPLACE ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_interruptible_flag (struct inode*) ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,...) ; 
 struct orangefs_kernel_op_s* op_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op_release (struct orangefs_kernel_op_s*) ; 
 int service_operation (struct orangefs_kernel_op_s*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (scalar_t__,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int orangefs_inode_removexattr(struct inode *inode, const char *name,
				      int flags)
{
	struct orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	struct orangefs_kernel_op_s *new_op = NULL;
	int ret = -ENOMEM;

	if (strlen(name) >= ORANGEFS_MAX_XATTR_NAMELEN)
		return -EINVAL;

	down_write(&orangefs_inode->xattr_sem);
	new_op = op_alloc(ORANGEFS_VFS_OP_REMOVEXATTR);
	if (!new_op)
		goto out_unlock;

	new_op->upcall.req.removexattr.refn = orangefs_inode->refn;
	/*
	 * NOTE: Although keys are meant to be NULL terminated
	 * textual strings, I am going to explicitly pass the
	 * length just in case we change this later on...
	 */
	strcpy(new_op->upcall.req.removexattr.key, name);
	new_op->upcall.req.removexattr.key_sz = strlen(name) + 1;

	gossip_debug(GOSSIP_XATTR_DEBUG,
		     "orangefs_inode_removexattr: key %s, key_sz %d\n",
		     (char *)new_op->upcall.req.removexattr.key,
		     (int)new_op->upcall.req.removexattr.key_sz);

	ret = service_operation(new_op,
				"orangefs_inode_removexattr",
				get_interruptible_flag(inode));
	if (ret == -ENOENT) {
		/*
		 * Request to replace a non-existent attribute is an error.
		 */
		if (flags & XATTR_REPLACE)
			ret = -ENODATA;
		else
			ret = 0;
	}

	gossip_debug(GOSSIP_XATTR_DEBUG,
		     "orangefs_inode_removexattr: returning %d\n", ret);

	op_release(new_op);
out_unlock:
	up_write(&orangefs_inode->xattr_sem);
	return ret;
}