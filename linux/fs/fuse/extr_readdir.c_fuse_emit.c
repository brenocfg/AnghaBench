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
struct fuse_file {int open_flags; } ;
struct fuse_dirent {int /*<<< orphan*/  type; int /*<<< orphan*/  ino; int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
struct file {struct fuse_file* private_data; } ;
struct dir_context {int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 int FOPEN_CACHE_DIR ; 
 int dir_emit (struct dir_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_add_dirent_to_cache (struct file*,struct fuse_dirent*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool fuse_emit(struct file *file, struct dir_context *ctx,
		      struct fuse_dirent *dirent)
{
	struct fuse_file *ff = file->private_data;

	if (ff->open_flags & FOPEN_CACHE_DIR)
		fuse_add_dirent_to_cache(file, dirent, ctx->pos);

	return dir_emit(ctx, dirent->name, dirent->namelen, dirent->ino,
			dirent->type);
}