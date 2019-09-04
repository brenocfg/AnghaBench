#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct fuse_lk_out {int /*<<< orphan*/  lk; } ;
struct fuse_lk_in {int dummy; } ;
struct fuse_conn {int dummy; } ;
struct file_lock {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  outarg ;
struct TYPE_8__ {int numargs; TYPE_1__* args; } ;
struct TYPE_9__ {TYPE_2__ out; } ;
struct TYPE_7__ {int size; struct fuse_lk_out* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_ARGS (TYPE_3__) ; 
 int /*<<< orphan*/  FUSE_GETLK ; 
 TYPE_3__ args ; 
 int convert_fuse_file_lock (struct fuse_conn*,int /*<<< orphan*/ *,struct file_lock*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  fuse_lk_fill (TYPE_3__*,struct file*,struct file_lock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fuse_lk_in*) ; 
 int fuse_simple_request (struct fuse_conn*,TYPE_3__*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 

__attribute__((used)) static int fuse_getlk(struct file *file, struct file_lock *fl)
{
	struct inode *inode = file_inode(file);
	struct fuse_conn *fc = get_fuse_conn(inode);
	FUSE_ARGS(args);
	struct fuse_lk_in inarg;
	struct fuse_lk_out outarg;
	int err;

	fuse_lk_fill(&args, file, fl, FUSE_GETLK, 0, 0, &inarg);
	args.out.numargs = 1;
	args.out.args[0].size = sizeof(outarg);
	args.out.args[0].value = &outarg;
	err = fuse_simple_request(fc, &args);
	if (!err)
		err = convert_fuse_file_lock(fc, &outarg.lk, fl);

	return err;
}