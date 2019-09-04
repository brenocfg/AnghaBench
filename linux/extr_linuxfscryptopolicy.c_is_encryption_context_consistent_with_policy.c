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
struct fscrypt_policy {scalar_t__ flags; scalar_t__ contents_encryption_mode; scalar_t__ filenames_encryption_mode; int /*<<< orphan*/  master_key_descriptor; } ;
struct fscrypt_context {scalar_t__ flags; scalar_t__ contents_encryption_mode; scalar_t__ filenames_encryption_mode; int /*<<< orphan*/  master_key_descriptor; } ;

/* Variables and functions */
 int /*<<< orphan*/  FS_KEY_DESCRIPTOR_SIZE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_encryption_context_consistent_with_policy(
				const struct fscrypt_context *ctx,
				const struct fscrypt_policy *policy)
{
	return memcmp(ctx->master_key_descriptor, policy->master_key_descriptor,
		      FS_KEY_DESCRIPTOR_SIZE) == 0 &&
		(ctx->flags == policy->flags) &&
		(ctx->contents_encryption_mode ==
		 policy->contents_encryption_mode) &&
		(ctx->filenames_encryption_mode ==
		 policy->filenames_encryption_mode);
}