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
typedef  int /*<<< orphan*/  u8 ;
struct fscrypt_mode {int /*<<< orphan*/  needs_essiv; int /*<<< orphan*/  friendly_name; } ;
struct TYPE_3__ {scalar_t__ contents_encryption_mode; scalar_t__ filenames_encryption_mode; } ;
struct TYPE_4__ {TYPE_1__ v1; } ;
struct fscrypt_info {int /*<<< orphan*/  ci_ctfm; struct fscrypt_direct_key* ci_direct_key; int /*<<< orphan*/  ci_inode; TYPE_2__ ci_policy; struct fscrypt_mode* ci_mode; } ;
struct fscrypt_direct_key {int /*<<< orphan*/  dk_ctfm; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct fscrypt_direct_key*) ; 
 int PTR_ERR (struct fscrypt_direct_key*) ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 struct fscrypt_direct_key* fscrypt_get_direct_key (struct fscrypt_info*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fscrypt_mode_supports_direct_key (struct fscrypt_mode const*) ; 
 int /*<<< orphan*/  fscrypt_warn (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int setup_v1_file_key_direct(struct fscrypt_info *ci,
				    const u8 *raw_master_key)
{
	const struct fscrypt_mode *mode = ci->ci_mode;
	struct fscrypt_direct_key *dk;

	if (!fscrypt_mode_supports_direct_key(mode)) {
		fscrypt_warn(ci->ci_inode,
			     "Direct key mode not allowed with %s",
			     mode->friendly_name);
		return -EINVAL;
	}

	if (ci->ci_policy.v1.contents_encryption_mode !=
	    ci->ci_policy.v1.filenames_encryption_mode) {
		fscrypt_warn(ci->ci_inode,
			     "Direct key mode not allowed with different contents and filenames modes");
		return -EINVAL;
	}

	/* ESSIV implies 16-byte IVs which implies !DIRECT_KEY */
	if (WARN_ON(mode->needs_essiv))
		return -EINVAL;

	dk = fscrypt_get_direct_key(ci, raw_master_key);
	if (IS_ERR(dk))
		return PTR_ERR(dk);
	ci->ci_direct_key = dk;
	ci->ci_ctfm = dk->dk_ctfm;
	return 0;
}