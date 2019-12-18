#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/  hkdf; } ;
struct fscrypt_master_key {TYPE_1__ mk_secret; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_7__ {TYPE_2__ v2; } ;
struct fscrypt_info {TYPE_4__* ci_mode; int /*<<< orphan*/  ci_nonce; int /*<<< orphan*/  ci_inode; TYPE_3__ ci_policy; } ;
struct TYPE_8__ {int /*<<< orphan*/  keysize; int /*<<< orphan*/  friendly_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int FSCRYPT_MAX_KEY_SIZE ; 
 int FSCRYPT_POLICY_FLAG_DIRECT_KEY ; 
 int /*<<< orphan*/  FS_KEY_DERIVATION_NONCE_SIZE ; 
 int /*<<< orphan*/  HKDF_CONTEXT_PER_FILE_KEY ; 
 int fscrypt_hkdf_expand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscrypt_mode_supports_direct_key (TYPE_4__*) ; 
 int fscrypt_set_derived_key (struct fscrypt_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscrypt_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memzero_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int setup_per_mode_key (struct fscrypt_info*,struct fscrypt_master_key*) ; 

__attribute__((used)) static int fscrypt_setup_v2_file_key(struct fscrypt_info *ci,
				     struct fscrypt_master_key *mk)
{
	u8 derived_key[FSCRYPT_MAX_KEY_SIZE];
	int err;

	if (ci->ci_policy.v2.flags & FSCRYPT_POLICY_FLAG_DIRECT_KEY) {
		/*
		 * DIRECT_KEY: instead of deriving per-file keys, the per-file
		 * nonce will be included in all the IVs.  But unlike v1
		 * policies, for v2 policies in this case we don't encrypt with
		 * the master key directly but rather derive a per-mode key.
		 * This ensures that the master key is consistently used only
		 * for HKDF, avoiding key reuse issues.
		 */
		if (!fscrypt_mode_supports_direct_key(ci->ci_mode)) {
			fscrypt_warn(ci->ci_inode,
				     "Direct key flag not allowed with %s",
				     ci->ci_mode->friendly_name);
			return -EINVAL;
		}
		return setup_per_mode_key(ci, mk);
	}

	err = fscrypt_hkdf_expand(&mk->mk_secret.hkdf,
				  HKDF_CONTEXT_PER_FILE_KEY,
				  ci->ci_nonce, FS_KEY_DERIVATION_NONCE_SIZE,
				  derived_key, ci->ci_mode->keysize);
	if (err)
		return err;

	err = fscrypt_set_derived_key(ci, derived_key);
	memzero_explicit(derived_key, ci->ci_mode->keysize);
	return err;
}