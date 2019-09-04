#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct orangefs_kernel_op_s {int dummy; } ;
struct orangefs_inode_s {int dummy; } ;
struct orangefs_dir {int error; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ORANGEFS_VFS_OP_READDIR ; 
 int do_readdir (struct orangefs_inode_s*,struct orangefs_dir*,struct dentry*,struct orangefs_kernel_op_s*) ; 
 struct orangefs_kernel_op_s* op_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op_release (struct orangefs_kernel_op_s*) ; 
 int parse_readdir (struct orangefs_dir*,struct orangefs_kernel_op_s*) ; 

__attribute__((used)) static int orangefs_dir_more(struct orangefs_inode_s *oi,
    struct orangefs_dir *od, struct dentry *dentry)
{
	struct orangefs_kernel_op_s *op;
	int r;

	op = op_alloc(ORANGEFS_VFS_OP_READDIR);
	if (!op) {
		od->error = -ENOMEM;
		return -ENOMEM;
	}
	r = do_readdir(oi, od, dentry, op);
	if (r) {
		od->error = r;
		goto out;
	}
	r = parse_readdir(od, op);
	if (r) {
		od->error = r;
		goto out;
	}

	od->error = 0;
out:
	op_release(op);
	return od->error;
}