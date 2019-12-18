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
struct TYPE_2__ {unsigned int cache_off; int /*<<< orphan*/  pos; } ;
struct fuse_file {TYPE_1__ readdir; } ;
struct fuse_dirent {scalar_t__ namelen; int /*<<< orphan*/  off; int /*<<< orphan*/  type; int /*<<< orphan*/  ino; int /*<<< orphan*/  name; } ;
struct dir_context {int /*<<< orphan*/  pos; } ;
typedef  enum fuse_parse_result { ____Placeholder_fuse_parse_result } fuse_parse_result ;

/* Variables and functions */
 int FOUND_ALL ; 
 int FOUND_ERR ; 
 int FOUND_NONE ; 
 int FOUND_SOME ; 
 size_t FUSE_DIRENT_SIZE (struct fuse_dirent*) ; 
 scalar_t__ FUSE_NAME_MAX ; 
 unsigned int FUSE_NAME_OFFSET ; 
 unsigned int PAGE_MASK ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dir_emit (struct dir_context*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * memchr (int /*<<< orphan*/ ,char,scalar_t__) ; 

__attribute__((used)) static enum fuse_parse_result fuse_parse_cache(struct fuse_file *ff,
					       void *addr, unsigned int size,
					       struct dir_context *ctx)
{
	unsigned int offset = ff->readdir.cache_off & ~PAGE_MASK;
	enum fuse_parse_result res = FOUND_NONE;

	WARN_ON(offset >= size);

	for (;;) {
		struct fuse_dirent *dirent = addr + offset;
		unsigned int nbytes = size - offset;
		size_t reclen;

		if (nbytes < FUSE_NAME_OFFSET || !dirent->namelen)
			break;

		reclen = FUSE_DIRENT_SIZE(dirent); /* derefs ->namelen */

		if (WARN_ON(dirent->namelen > FUSE_NAME_MAX))
			return FOUND_ERR;
		if (WARN_ON(reclen > nbytes))
			return FOUND_ERR;
		if (WARN_ON(memchr(dirent->name, '/', dirent->namelen) != NULL))
			return FOUND_ERR;

		if (ff->readdir.pos == ctx->pos) {
			res = FOUND_SOME;
			if (!dir_emit(ctx, dirent->name, dirent->namelen,
				      dirent->ino, dirent->type))
				return FOUND_ALL;
			ctx->pos = dirent->off;
		}
		ff->readdir.pos = dirent->off;
		ff->readdir.cache_off += reclen;

		offset += reclen;
	}

	return res;
}