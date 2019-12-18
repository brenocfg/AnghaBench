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
typedef  int /*<<< orphan*/  u32 ;
struct inode {struct fscrypt_info* i_crypt_info; } ;
struct fscrypt_info {int /*<<< orphan*/  ci_policy; } ;

/* Variables and functions */
 int FSCRYPT_POLICY_FLAGS_PAD_MASK ; 
 scalar_t__ FS_CRYPTO_BLOCK_SIZE ; 
 int fscrypt_policy_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_up (int /*<<< orphan*/ ,int) ; 

bool fscrypt_fname_encrypted_size(const struct inode *inode, u32 orig_len,
				  u32 max_len, u32 *encrypted_len_ret)
{
	const struct fscrypt_info *ci = inode->i_crypt_info;
	int padding = 4 << (fscrypt_policy_flags(&ci->ci_policy) &
			    FSCRYPT_POLICY_FLAGS_PAD_MASK);
	u32 encrypted_len;

	if (orig_len > max_len)
		return false;
	encrypted_len = max(orig_len, (u32)FS_CRYPTO_BLOCK_SIZE);
	encrypted_len = round_up(encrypted_len, padding);
	*encrypted_len_ret = min(encrypted_len, max_len);
	return true;
}