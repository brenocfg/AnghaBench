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
struct fuse_release_in {int /*<<< orphan*/  lock_owner; int /*<<< orphan*/  release_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  inode; struct fuse_release_in in; } ;
struct TYPE_5__ {TYPE_1__ release; } ;
struct fuse_req {TYPE_2__ misc; } ;
struct fuse_file {TYPE_3__* fc; scalar_t__ flock; struct fuse_req* reserved_req; } ;
struct file {int /*<<< orphan*/  f_flags; struct fuse_file* private_data; } ;
typedef  int /*<<< orphan*/  fl_owner_t ;
struct TYPE_6__ {int /*<<< orphan*/ * destroy_req; } ;

/* Variables and functions */
 int FUSE_RELEASE ; 
 int FUSE_RELEASEDIR ; 
 int /*<<< orphan*/  FUSE_RELEASE_FLOCK_UNLOCK ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  fuse_file_put (struct fuse_file*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fuse_lock_owner_id (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_prepare_release (struct fuse_file*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  igrab (int /*<<< orphan*/ ) ; 

void fuse_release_common(struct file *file, bool isdir)
{
	struct fuse_file *ff = file->private_data;
	struct fuse_req *req = ff->reserved_req;
	int opcode = isdir ? FUSE_RELEASEDIR : FUSE_RELEASE;

	fuse_prepare_release(ff, file->f_flags, opcode);

	if (ff->flock) {
		struct fuse_release_in *inarg = &req->misc.release.in;
		inarg->release_flags |= FUSE_RELEASE_FLOCK_UNLOCK;
		inarg->lock_owner = fuse_lock_owner_id(ff->fc,
						       (fl_owner_t) file);
	}
	/* Hold inode until release is finished */
	req->misc.release.inode = igrab(file_inode(file));

	/*
	 * Normally this will send the RELEASE request, however if
	 * some asynchronous READ or WRITE requests are outstanding,
	 * the sending will be delayed.
	 *
	 * Make the release synchronous if this is a fuseblk mount,
	 * synchronous RELEASE is allowed (and desirable) in this case
	 * because the server can be trusted not to screw up.
	 */
	fuse_file_put(ff, ff->fc->destroy_req != NULL, isdir);
}