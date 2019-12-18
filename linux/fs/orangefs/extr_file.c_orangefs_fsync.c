#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  refn; } ;
struct TYPE_8__ {TYPE_1__ fsync; } ;
struct TYPE_9__ {TYPE_2__ req; } ;
struct orangefs_kernel_op_s {TYPE_3__ upcall; } ;
struct orangefs_inode_s {int /*<<< orphan*/  refn; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_10__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GOSSIP_FILE_DEBUG ; 
 struct orangefs_inode_s* ORANGEFS_I (TYPE_4__*) ; 
 int /*<<< orphan*/  ORANGEFS_VFS_OP_FSYNC ; 
 TYPE_4__* file_inode (struct file*) ; 
 int filemap_write_and_wait_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_interruptible_flag (TYPE_4__*) ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,int) ; 
 struct orangefs_kernel_op_s* op_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op_release (struct orangefs_kernel_op_s*) ; 
 int service_operation (struct orangefs_kernel_op_s*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int orangefs_fsync(struct file *file,
		       loff_t start,
		       loff_t end,
		       int datasync)
{
	int ret;
	struct orangefs_inode_s *orangefs_inode =
		ORANGEFS_I(file_inode(file));
	struct orangefs_kernel_op_s *new_op = NULL;

	ret = filemap_write_and_wait_range(file_inode(file)->i_mapping,
	    start, end);
	if (ret < 0)
		return ret;

	new_op = op_alloc(ORANGEFS_VFS_OP_FSYNC);
	if (!new_op)
		return -ENOMEM;
	new_op->upcall.req.fsync.refn = orangefs_inode->refn;

	ret = service_operation(new_op,
			"orangefs_fsync",
			get_interruptible_flag(file_inode(file)));

	gossip_debug(GOSSIP_FILE_DEBUG,
		     "orangefs_fsync got return value of %d\n",
		     ret);

	op_release(new_op);
	return ret;
}