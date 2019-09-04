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
struct inode {TYPE_2__* i_sb; } ;
struct fscrypt_policy {int flags; int /*<<< orphan*/  filenames_encryption_mode; int /*<<< orphan*/  contents_encryption_mode; int /*<<< orphan*/  master_key_descriptor; } ;
struct fscrypt_context {int flags; int /*<<< orphan*/  nonce; int /*<<< orphan*/  filenames_encryption_mode; int /*<<< orphan*/  contents_encryption_mode; int /*<<< orphan*/  master_key_descriptor; int /*<<< orphan*/  format; } ;
typedef  int /*<<< orphan*/  ctx ;
struct TYPE_4__ {TYPE_1__* s_cop; } ;
struct TYPE_3__ {int (* set_context ) (struct inode*,struct fscrypt_context*,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FS_ENCRYPTION_CONTEXT_FORMAT_V1 ; 
 int FS_KEY_DERIVATION_NONCE_SIZE ; 
 int /*<<< orphan*/  FS_KEY_DESCRIPTOR_SIZE ; 
 int FS_POLICY_FLAGS_VALID ; 
 int /*<<< orphan*/  fscrypt_valid_enc_modes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct inode*,struct fscrypt_context*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_encryption_context_from_policy(struct inode *inode,
				const struct fscrypt_policy *policy)
{
	struct fscrypt_context ctx;

	ctx.format = FS_ENCRYPTION_CONTEXT_FORMAT_V1;
	memcpy(ctx.master_key_descriptor, policy->master_key_descriptor,
					FS_KEY_DESCRIPTOR_SIZE);

	if (!fscrypt_valid_enc_modes(policy->contents_encryption_mode,
				     policy->filenames_encryption_mode))
		return -EINVAL;

	if (policy->flags & ~FS_POLICY_FLAGS_VALID)
		return -EINVAL;

	ctx.contents_encryption_mode = policy->contents_encryption_mode;
	ctx.filenames_encryption_mode = policy->filenames_encryption_mode;
	ctx.flags = policy->flags;
	BUILD_BUG_ON(sizeof(ctx.nonce) != FS_KEY_DERIVATION_NONCE_SIZE);
	get_random_bytes(ctx.nonce, FS_KEY_DERIVATION_NONCE_SIZE);

	return inode->i_sb->s_cop->set_context(inode, &ctx, sizeof(ctx), NULL);
}