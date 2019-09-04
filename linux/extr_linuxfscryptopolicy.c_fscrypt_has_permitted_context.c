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
struct inode {struct fscrypt_info* i_crypt_info; int /*<<< orphan*/  i_mode; TYPE_1__* i_sb; } ;
struct fscrypt_operations {int (* get_context ) (struct inode*,struct fscrypt_context*,int) ;} ;
struct fscrypt_info {scalar_t__ ci_data_mode; scalar_t__ ci_filename_mode; scalar_t__ ci_flags; int /*<<< orphan*/  ci_master_key; } ;
struct fscrypt_context {scalar_t__ contents_encryption_mode; scalar_t__ filenames_encryption_mode; scalar_t__ flags; int /*<<< orphan*/  master_key_descriptor; } ;
typedef  int /*<<< orphan*/  parent_ctx ;
typedef  int /*<<< orphan*/  child_ctx ;
struct TYPE_2__ {struct fscrypt_operations* s_cop; } ;

/* Variables and functions */
 int /*<<< orphan*/  FS_KEY_DESCRIPTOR_SIZE ; 
 int /*<<< orphan*/  IS_ENCRYPTED (struct inode*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int fscrypt_get_encryption_info (struct inode*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct inode*,struct fscrypt_context*,int) ; 
 int stub2 (struct inode*,struct fscrypt_context*,int) ; 

int fscrypt_has_permitted_context(struct inode *parent, struct inode *child)
{
	const struct fscrypt_operations *cops = parent->i_sb->s_cop;
	const struct fscrypt_info *parent_ci, *child_ci;
	struct fscrypt_context parent_ctx, child_ctx;
	int res;

	/* No restrictions on file types which are never encrypted */
	if (!S_ISREG(child->i_mode) && !S_ISDIR(child->i_mode) &&
	    !S_ISLNK(child->i_mode))
		return 1;

	/* No restrictions if the parent directory is unencrypted */
	if (!IS_ENCRYPTED(parent))
		return 1;

	/* Encrypted directories must not contain unencrypted files */
	if (!IS_ENCRYPTED(child))
		return 0;

	/*
	 * Both parent and child are encrypted, so verify they use the same
	 * encryption policy.  Compare the fscrypt_info structs if the keys are
	 * available, otherwise retrieve and compare the fscrypt_contexts.
	 *
	 * Note that the fscrypt_context retrieval will be required frequently
	 * when accessing an encrypted directory tree without the key.
	 * Performance-wise this is not a big deal because we already don't
	 * really optimize for file access without the key (to the extent that
	 * such access is even possible), given that any attempted access
	 * already causes a fscrypt_context retrieval and keyring search.
	 *
	 * In any case, if an unexpected error occurs, fall back to "forbidden".
	 */

	res = fscrypt_get_encryption_info(parent);
	if (res)
		return 0;
	res = fscrypt_get_encryption_info(child);
	if (res)
		return 0;
	parent_ci = parent->i_crypt_info;
	child_ci = child->i_crypt_info;

	if (parent_ci && child_ci) {
		return memcmp(parent_ci->ci_master_key, child_ci->ci_master_key,
			      FS_KEY_DESCRIPTOR_SIZE) == 0 &&
			(parent_ci->ci_data_mode == child_ci->ci_data_mode) &&
			(parent_ci->ci_filename_mode ==
			 child_ci->ci_filename_mode) &&
			(parent_ci->ci_flags == child_ci->ci_flags);
	}

	res = cops->get_context(parent, &parent_ctx, sizeof(parent_ctx));
	if (res != sizeof(parent_ctx))
		return 0;

	res = cops->get_context(child, &child_ctx, sizeof(child_ctx));
	if (res != sizeof(child_ctx))
		return 0;

	return memcmp(parent_ctx.master_key_descriptor,
		      child_ctx.master_key_descriptor,
		      FS_KEY_DESCRIPTOR_SIZE) == 0 &&
		(parent_ctx.contents_encryption_mode ==
		 child_ctx.contents_encryption_mode) &&
		(parent_ctx.filenames_encryption_mode ==
		 child_ctx.filenames_encryption_mode) &&
		(parent_ctx.flags == child_ctx.flags);
}