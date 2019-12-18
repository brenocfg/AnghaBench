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
union fscrypt_iv {int /*<<< orphan*/  raw; int /*<<< orphan*/  nonce; int /*<<< orphan*/  lblk_num; } ;
typedef  int /*<<< orphan*/  u64 ;
struct fscrypt_info {int /*<<< orphan*/ * ci_essiv_tfm; int /*<<< orphan*/  ci_nonce; int /*<<< orphan*/  ci_policy; TYPE_1__* ci_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  ivsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  FS_KEY_DERIVATION_NONCE_SIZE ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_cipher_encrypt_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fscrypt_is_direct_key_policy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union fscrypt_iv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fscrypt_generate_iv(union fscrypt_iv *iv, u64 lblk_num,
			 const struct fscrypt_info *ci)
{
	memset(iv, 0, ci->ci_mode->ivsize);
	iv->lblk_num = cpu_to_le64(lblk_num);

	if (fscrypt_is_direct_key_policy(&ci->ci_policy))
		memcpy(iv->nonce, ci->ci_nonce, FS_KEY_DERIVATION_NONCE_SIZE);

	if (ci->ci_essiv_tfm != NULL)
		crypto_cipher_encrypt_one(ci->ci_essiv_tfm, iv->raw, iv->raw);
}