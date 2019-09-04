#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_2__* i_sb; struct fscrypt_info* i_crypt_info; } ;
struct fscrypt_info {int /*<<< orphan*/  ci_master_key; int /*<<< orphan*/  ci_flags; int /*<<< orphan*/  ci_filename_mode; int /*<<< orphan*/  ci_data_mode; } ;
struct fscrypt_context {int /*<<< orphan*/  nonce; int /*<<< orphan*/  master_key_descriptor; int /*<<< orphan*/  flags; int /*<<< orphan*/  filenames_encryption_mode; int /*<<< orphan*/  contents_encryption_mode; int /*<<< orphan*/  format; } ;
typedef  int /*<<< orphan*/  ctx ;
struct TYPE_4__ {TYPE_1__* s_cop; } ;
struct TYPE_3__ {int (* set_context ) (struct inode*,struct fscrypt_context*,int,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOKEY ; 
 int FSCRYPT_SET_CONTEXT_MAX_SIZE ; 
 int /*<<< orphan*/  FS_ENCRYPTION_CONTEXT_FORMAT_V1 ; 
 int /*<<< orphan*/  FS_KEY_DERIVATION_NONCE_SIZE ; 
 int /*<<< orphan*/  FS_KEY_DESCRIPTOR_SIZE ; 
 int fscrypt_get_encryption_info (struct inode*) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct inode*,struct fscrypt_context*,int,void*) ; 

int fscrypt_inherit_context(struct inode *parent, struct inode *child,
						void *fs_data, bool preload)
{
	struct fscrypt_context ctx;
	struct fscrypt_info *ci;
	int res;

	res = fscrypt_get_encryption_info(parent);
	if (res < 0)
		return res;

	ci = parent->i_crypt_info;
	if (ci == NULL)
		return -ENOKEY;

	ctx.format = FS_ENCRYPTION_CONTEXT_FORMAT_V1;
	ctx.contents_encryption_mode = ci->ci_data_mode;
	ctx.filenames_encryption_mode = ci->ci_filename_mode;
	ctx.flags = ci->ci_flags;
	memcpy(ctx.master_key_descriptor, ci->ci_master_key,
	       FS_KEY_DESCRIPTOR_SIZE);
	get_random_bytes(ctx.nonce, FS_KEY_DERIVATION_NONCE_SIZE);
	BUILD_BUG_ON(sizeof(ctx) != FSCRYPT_SET_CONTEXT_MAX_SIZE);
	res = parent->i_sb->s_cop->set_context(child, &ctx,
						sizeof(ctx), fs_data);
	if (res)
		return res;
	return preload ? fscrypt_get_encryption_info(child): 0;
}