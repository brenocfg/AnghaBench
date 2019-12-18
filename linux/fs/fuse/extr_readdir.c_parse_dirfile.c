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
struct fuse_dirent {scalar_t__ namelen; int /*<<< orphan*/  off; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;
struct dir_context {int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 int EIO ; 
 size_t FUSE_DIRENT_SIZE (struct fuse_dirent*) ; 
 scalar_t__ FUSE_NAME_MAX ; 
 size_t FUSE_NAME_OFFSET ; 
 int /*<<< orphan*/  fuse_emit (struct file*,struct dir_context*,struct fuse_dirent*) ; 
 int /*<<< orphan*/ * memchr (int /*<<< orphan*/ ,char,scalar_t__) ; 

__attribute__((used)) static int parse_dirfile(char *buf, size_t nbytes, struct file *file,
			 struct dir_context *ctx)
{
	while (nbytes >= FUSE_NAME_OFFSET) {
		struct fuse_dirent *dirent = (struct fuse_dirent *) buf;
		size_t reclen = FUSE_DIRENT_SIZE(dirent);
		if (!dirent->namelen || dirent->namelen > FUSE_NAME_MAX)
			return -EIO;
		if (reclen > nbytes)
			break;
		if (memchr(dirent->name, '/', dirent->namelen) != NULL)
			return -EIO;

		if (!fuse_emit(file, ctx, dirent))
			break;

		buf += reclen;
		nbytes -= reclen;
		ctx->pos = dirent->off;
	}

	return 0;
}