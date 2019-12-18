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
struct fscrypt_policy_v2 {int /*<<< orphan*/  master_key_identifier; int /*<<< orphan*/  flags; int /*<<< orphan*/  filenames_encryption_mode; int /*<<< orphan*/  contents_encryption_mode; } ;
struct fscrypt_policy_v1 {int /*<<< orphan*/  master_key_descriptor; int /*<<< orphan*/  flags; int /*<<< orphan*/  filenames_encryption_mode; int /*<<< orphan*/  contents_encryption_mode; } ;
union fscrypt_policy {int version; struct fscrypt_policy_v2 v2; struct fscrypt_policy_v1 v1; } ;
struct fscrypt_context_v2 {int /*<<< orphan*/  nonce; int /*<<< orphan*/  master_key_identifier; int /*<<< orphan*/  flags; int /*<<< orphan*/  filenames_encryption_mode; int /*<<< orphan*/  contents_encryption_mode; int /*<<< orphan*/  version; } ;
struct fscrypt_context_v1 {int /*<<< orphan*/  nonce; int /*<<< orphan*/  master_key_descriptor; int /*<<< orphan*/  flags; int /*<<< orphan*/  filenames_encryption_mode; int /*<<< orphan*/  contents_encryption_mode; int /*<<< orphan*/  version; } ;
union fscrypt_context {struct fscrypt_context_v2 v2; struct fscrypt_context_v1 v1; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  FSCRYPT_CONTEXT_V1 ; 
 int /*<<< orphan*/  FSCRYPT_CONTEXT_V2 ; 
#define  FSCRYPT_POLICY_V1 129 
#define  FSCRYPT_POLICY_V2 128 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (union fscrypt_context*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fscrypt_new_context_from_policy(union fscrypt_context *ctx_u,
					   const union fscrypt_policy *policy_u)
{
	memset(ctx_u, 0, sizeof(*ctx_u));

	switch (policy_u->version) {
	case FSCRYPT_POLICY_V1: {
		const struct fscrypt_policy_v1 *policy = &policy_u->v1;
		struct fscrypt_context_v1 *ctx = &ctx_u->v1;

		ctx->version = FSCRYPT_CONTEXT_V1;
		ctx->contents_encryption_mode =
			policy->contents_encryption_mode;
		ctx->filenames_encryption_mode =
			policy->filenames_encryption_mode;
		ctx->flags = policy->flags;
		memcpy(ctx->master_key_descriptor,
		       policy->master_key_descriptor,
		       sizeof(ctx->master_key_descriptor));
		get_random_bytes(ctx->nonce, sizeof(ctx->nonce));
		return sizeof(*ctx);
	}
	case FSCRYPT_POLICY_V2: {
		const struct fscrypt_policy_v2 *policy = &policy_u->v2;
		struct fscrypt_context_v2 *ctx = &ctx_u->v2;

		ctx->version = FSCRYPT_CONTEXT_V2;
		ctx->contents_encryption_mode =
			policy->contents_encryption_mode;
		ctx->filenames_encryption_mode =
			policy->filenames_encryption_mode;
		ctx->flags = policy->flags;
		memcpy(ctx->master_key_identifier,
		       policy->master_key_identifier,
		       sizeof(ctx->master_key_identifier));
		get_random_bytes(ctx->nonce, sizeof(ctx->nonce));
		return sizeof(*ctx);
	}
	}
	BUG();
}