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
struct fscrypt_policy_v2 {int flags; int /*<<< orphan*/  __reserved; int /*<<< orphan*/  filenames_encryption_mode; int /*<<< orphan*/  contents_encryption_mode; } ;
struct fscrypt_policy_v1 {int flags; int /*<<< orphan*/  filenames_encryption_mode; int /*<<< orphan*/  contents_encryption_mode; } ;
union fscrypt_policy {int version; struct fscrypt_policy_v2 v2; struct fscrypt_policy_v1 v1; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int FSCRYPT_POLICY_FLAGS_VALID ; 
#define  FSCRYPT_POLICY_V1 129 
#define  FSCRYPT_POLICY_V2 128 
 int /*<<< orphan*/  fscrypt_valid_enc_modes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscrypt_warn (struct inode const*,char*,...) ; 
 int /*<<< orphan*/  memchr_inv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

bool fscrypt_supported_policy(const union fscrypt_policy *policy_u,
			      const struct inode *inode)
{
	switch (policy_u->version) {
	case FSCRYPT_POLICY_V1: {
		const struct fscrypt_policy_v1 *policy = &policy_u->v1;

		if (!fscrypt_valid_enc_modes(policy->contents_encryption_mode,
					     policy->filenames_encryption_mode)) {
			fscrypt_warn(inode,
				     "Unsupported encryption modes (contents %d, filenames %d)",
				     policy->contents_encryption_mode,
				     policy->filenames_encryption_mode);
			return false;
		}

		if (policy->flags & ~FSCRYPT_POLICY_FLAGS_VALID) {
			fscrypt_warn(inode,
				     "Unsupported encryption flags (0x%02x)",
				     policy->flags);
			return false;
		}

		return true;
	}
	case FSCRYPT_POLICY_V2: {
		const struct fscrypt_policy_v2 *policy = &policy_u->v2;

		if (!fscrypt_valid_enc_modes(policy->contents_encryption_mode,
					     policy->filenames_encryption_mode)) {
			fscrypt_warn(inode,
				     "Unsupported encryption modes (contents %d, filenames %d)",
				     policy->contents_encryption_mode,
				     policy->filenames_encryption_mode);
			return false;
		}

		if (policy->flags & ~FSCRYPT_POLICY_FLAGS_VALID) {
			fscrypt_warn(inode,
				     "Unsupported encryption flags (0x%02x)",
				     policy->flags);
			return false;
		}

		if (memchr_inv(policy->__reserved, 0,
			       sizeof(policy->__reserved))) {
			fscrypt_warn(inode,
				     "Reserved bits set in encryption policy");
			return false;
		}

		return true;
	}
	}
	return false;
}