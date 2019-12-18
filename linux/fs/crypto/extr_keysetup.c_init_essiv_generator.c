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
typedef  int /*<<< orphan*/  u8 ;
struct fscrypt_info {struct crypto_cipher* ci_essiv_tfm; TYPE_1__* ci_mode; } ;
struct crypto_cipher {int dummy; } ;
typedef  int /*<<< orphan*/  salt ;
struct TYPE_2__ {scalar_t__ ivsize; } ;

/* Variables and functions */
 scalar_t__ AES_BLOCK_SIZE ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct crypto_cipher*) ; 
 int PTR_ERR (struct crypto_cipher*) ; 
 int SHA256_DIGEST_SIZE ; 
 scalar_t__ WARN_ON (int) ; 
 struct crypto_cipher* crypto_alloc_cipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_cipher_setkey (struct crypto_cipher*,int /*<<< orphan*/ *,int) ; 
 int derive_essiv_salt (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memzero_explicit (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int init_essiv_generator(struct fscrypt_info *ci, const u8 *raw_key,
				int keysize)
{
	int err;
	struct crypto_cipher *essiv_tfm;
	u8 salt[SHA256_DIGEST_SIZE];

	if (WARN_ON(ci->ci_mode->ivsize != AES_BLOCK_SIZE))
		return -EINVAL;

	essiv_tfm = crypto_alloc_cipher("aes", 0, 0);
	if (IS_ERR(essiv_tfm))
		return PTR_ERR(essiv_tfm);

	ci->ci_essiv_tfm = essiv_tfm;

	err = derive_essiv_salt(raw_key, keysize, salt);
	if (err)
		goto out;

	/*
	 * Using SHA256 to derive the salt/key will result in AES-256 being
	 * used for IV generation. File contents encryption will still use the
	 * configured keysize (AES-128) nevertheless.
	 */
	err = crypto_cipher_setkey(essiv_tfm, salt, sizeof(salt));
	if (err)
		goto out;

out:
	memzero_explicit(salt, sizeof(salt));
	return err;
}