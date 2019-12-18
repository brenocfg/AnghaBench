#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  nodeid; } ;
struct fuse_dirent {scalar_t__ namelen; int /*<<< orphan*/  off; int /*<<< orphan*/  name; } ;
struct fuse_direntplus {TYPE_1__ entry_out; struct fuse_dirent dirent; } ;
struct file {int dummy; } ;
struct dir_context {int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 int EIO ; 
 size_t FUSE_DIRENTPLUS_SIZE (struct fuse_direntplus*) ; 
 scalar_t__ FUSE_NAME_MAX ; 
 size_t FUSE_NAME_OFFSET_DIRENTPLUS ; 
 int fuse_direntplus_link (struct file*,struct fuse_direntplus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_emit (struct file*,struct dir_context*,struct fuse_dirent*) ; 
 int /*<<< orphan*/  fuse_force_forget (struct file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * memchr (int /*<<< orphan*/ ,char,scalar_t__) ; 

__attribute__((used)) static int parse_dirplusfile(char *buf, size_t nbytes, struct file *file,
			     struct dir_context *ctx, u64 attr_version)
{
	struct fuse_direntplus *direntplus;
	struct fuse_dirent *dirent;
	size_t reclen;
	int over = 0;
	int ret;

	while (nbytes >= FUSE_NAME_OFFSET_DIRENTPLUS) {
		direntplus = (struct fuse_direntplus *) buf;
		dirent = &direntplus->dirent;
		reclen = FUSE_DIRENTPLUS_SIZE(direntplus);

		if (!dirent->namelen || dirent->namelen > FUSE_NAME_MAX)
			return -EIO;
		if (reclen > nbytes)
			break;
		if (memchr(dirent->name, '/', dirent->namelen) != NULL)
			return -EIO;

		if (!over) {
			/* We fill entries into dstbuf only as much as
			   it can hold. But we still continue iterating
			   over remaining entries to link them. If not,
			   we need to send a FORGET for each of those
			   which we did not link.
			*/
			over = !fuse_emit(file, ctx, dirent);
			if (!over)
				ctx->pos = dirent->off;
		}

		buf += reclen;
		nbytes -= reclen;

		ret = fuse_direntplus_link(file, direntplus, attr_version);
		if (ret)
			fuse_force_forget(file, direntplus->entry_out.nodeid);
	}

	return 0;
}