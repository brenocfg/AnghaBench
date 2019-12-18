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
struct fuse_release_in {int dummy; } ;
struct TYPE_6__ {int in_numargs; int opcode; int force; int nocreds; int /*<<< orphan*/  nodeid; TYPE_1__* in_args; } ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  fh; } ;
struct fuse_release_args {TYPE_3__ args; TYPE_2__ inarg; } ;
struct fuse_inode {int /*<<< orphan*/  lock; } ;
struct fuse_file {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  fh; int /*<<< orphan*/  poll_wait; int /*<<< orphan*/  polled_node; int /*<<< orphan*/  write_entry; struct fuse_release_args* release_args; struct fuse_conn* fc; } ;
struct fuse_conn {int /*<<< orphan*/  lock; int /*<<< orphan*/  polled_files; } ;
struct TYPE_4__ {int size; TYPE_2__* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (struct fuse_inode*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fuse_prepare_release(struct fuse_inode *fi, struct fuse_file *ff,
				 int flags, int opcode)
{
	struct fuse_conn *fc = ff->fc;
	struct fuse_release_args *ra = ff->release_args;

	/* Inode is NULL on error path of fuse_create_open() */
	if (likely(fi)) {
		spin_lock(&fi->lock);
		list_del(&ff->write_entry);
		spin_unlock(&fi->lock);
	}
	spin_lock(&fc->lock);
	if (!RB_EMPTY_NODE(&ff->polled_node))
		rb_erase(&ff->polled_node, &fc->polled_files);
	spin_unlock(&fc->lock);

	wake_up_interruptible_all(&ff->poll_wait);

	ra->inarg.fh = ff->fh;
	ra->inarg.flags = flags;
	ra->args.in_numargs = 1;
	ra->args.in_args[0].size = sizeof(struct fuse_release_in);
	ra->args.in_args[0].value = &ra->inarg;
	ra->args.opcode = opcode;
	ra->args.nodeid = ff->nodeid;
	ra->args.force = true;
	ra->args.nocreds = true;
}