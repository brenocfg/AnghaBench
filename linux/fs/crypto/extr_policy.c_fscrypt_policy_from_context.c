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
struct fscrypt_policy_v2 {int /*<<< orphan*/  master_key_identifier; int /*<<< orphan*/  __reserved; int /*<<< orphan*/  flags; int /*<<< orphan*/  filenames_encryption_mode; int /*<<< orphan*/  contents_encryption_mode; int /*<<< orphan*/  version; } ;
struct fscrypt_policy_v1 {int /*<<< orphan*/  master_key_descriptor; int /*<<< orphan*/  flags; int /*<<< orphan*/  filenames_encryption_mode; int /*<<< orphan*/  contents_encryption_mode; int /*<<< orphan*/  version; } ;
union fscrypt_policy {struct fscrypt_policy_v2 v2; struct fscrypt_policy_v1 v1; } ;
struct fscrypt_context_v2 {int /*<<< orphan*/  master_key_identifier; int /*<<< orphan*/  __reserved; int /*<<< orphan*/  flags; int /*<<< orphan*/  filenames_encryption_mode; int /*<<< orphan*/  contents_encryption_mode; } ;
struct fscrypt_context_v1 {int /*<<< orphan*/  master_key_descriptor; int /*<<< orphan*/  flags; int /*<<< orphan*/  filenames_encryption_mode; int /*<<< orphan*/  contents_encryption_mode; } ;
union fscrypt_context {int version; struct fscrypt_context_v2 v2; struct fscrypt_context_v1 v1; } ;

/* Variables and functions */
 int EINVAL ; 
#define  FSCRYPT_CONTEXT_V1 129 
#define  FSCRYPT_CONTEXT_V2 128 
 int /*<<< orphan*/  FSCRYPT_POLICY_V1 ; 
 int /*<<< orphan*/  FSCRYPT_POLICY_V2 ; 
 int fscrypt_context_size (union fscrypt_context const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (union fscrypt_policy*,int /*<<< orphan*/ ,int) ; 

int fscrypt_policy_from_context(union fscrypt_policy *policy_u,
				const union fscrypt_context *ctx_u,
				int ctx_size)
{
	memset(policy_u, 0, sizeof(*policy_u));

	if (ctx_size <= 0 || ctx_size != fscrypt_context_size(ctx_u))
		return -EINVAL;

	switch (ctx_u->version) {
	case FSCRYPT_CONTEXT_V1: {
		const struct fscrypt_context_v1 *ctx = &ctx_u->v1;
		struct fscrypt_policy_v1 *policy = &policy_u->v1;

		policy->version = FSCRYPT_POLICY_V1;
		policy->contents_encryption_mode =
			ctx->contents_encryption_mode;
		policy->filenames_encryption_mode =
			ctx->filenames_encryption_mode;
		policy->flags = ctx->flags;
		memcpy(policy->master_key_descriptor,
		       ctx->master_key_descriptor,
		       sizeof(policy->master_key_descriptor));
		return 0;
	}
	case FSCRYPT_CONTEXT_V2: {
		const struct fscrypt_context_v2 *ctx = &ctx_u->v2;
		struct fscrypt_policy_v2 *policy = &policy_u->v2;

		policy->version = FSCRYPT_POLICY_V2;
		policy->contents_encryption_mode =
			ctx->contents_encryption_mode;
		policy->filenames_encryption_mode =
			ctx->filenames_encryption_mode;
		policy->flags = ctx->flags;
		memcpy(policy->__reserved, ctx->__reserved,
		       sizeof(policy->__reserved));
		memcpy(policy->master_key_identifier,
		       ctx->master_key_identifier,
		       sizeof(policy->master_key_identifier));
		return 0;
	}
	}
	/* unreachable */
	return -EINVAL;
}