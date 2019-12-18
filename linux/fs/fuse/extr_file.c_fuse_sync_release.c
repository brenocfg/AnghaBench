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
struct fuse_inode {int dummy; } ;
struct fuse_file {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_RELEASE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  fuse_file_put (struct fuse_file*,int,int) ; 
 int /*<<< orphan*/  fuse_prepare_release (struct fuse_inode*,struct fuse_file*,int,int /*<<< orphan*/ ) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 

void fuse_sync_release(struct fuse_inode *fi, struct fuse_file *ff, int flags)
{
	WARN_ON(refcount_read(&ff->count) > 1);
	fuse_prepare_release(fi, ff, flags, FUSE_RELEASE);
	/*
	 * iput(NULL) is a no-op and since the refcount is 1 and everything's
	 * synchronous, we are fine with not doing igrab() here"
	 */
	fuse_file_put(ff, true, false);
}