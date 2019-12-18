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
struct inode {int dummy; } ;
struct fscrypt_mode {int logged_impl_name; int /*<<< orphan*/  keysize; int /*<<< orphan*/  friendly_name; int /*<<< orphan*/  cipher_str; } ;
struct crypto_skcipher {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  cra_driver_name; } ;
struct TYPE_4__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_FORBID_WEAK_KEYS ; 
 int /*<<< orphan*/  ENOENT ; 
 int ENOPKG ; 
 struct crypto_skcipher* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  PTR_ERR (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_alloc_skcipher (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_skcipher (struct crypto_skcipher*) ; 
 TYPE_2__* crypto_skcipher_alg (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_set_flags (struct crypto_skcipher*,int /*<<< orphan*/ ) ; 
 int crypto_skcipher_setkey (struct crypto_skcipher*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscrypt_err (struct inode const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscrypt_warn (struct inode const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct crypto_skcipher *fscrypt_allocate_skcipher(struct fscrypt_mode *mode,
						  const u8 *raw_key,
						  const struct inode *inode)
{
	struct crypto_skcipher *tfm;
	int err;

	tfm = crypto_alloc_skcipher(mode->cipher_str, 0, 0);
	if (IS_ERR(tfm)) {
		if (PTR_ERR(tfm) == -ENOENT) {
			fscrypt_warn(inode,
				     "Missing crypto API support for %s (API name: \"%s\")",
				     mode->friendly_name, mode->cipher_str);
			return ERR_PTR(-ENOPKG);
		}
		fscrypt_err(inode, "Error allocating '%s' transform: %ld",
			    mode->cipher_str, PTR_ERR(tfm));
		return tfm;
	}
	if (unlikely(!mode->logged_impl_name)) {
		/*
		 * fscrypt performance can vary greatly depending on which
		 * crypto algorithm implementation is used.  Help people debug
		 * performance problems by logging the ->cra_driver_name the
		 * first time a mode is used.  Note that multiple threads can
		 * race here, but it doesn't really matter.
		 */
		mode->logged_impl_name = true;
		pr_info("fscrypt: %s using implementation \"%s\"\n",
			mode->friendly_name,
			crypto_skcipher_alg(tfm)->base.cra_driver_name);
	}
	crypto_skcipher_set_flags(tfm, CRYPTO_TFM_REQ_FORBID_WEAK_KEYS);
	err = crypto_skcipher_setkey(tfm, raw_key, mode->keysize);
	if (err)
		goto err_free_tfm;

	return tfm;

err_free_tfm:
	crypto_free_skcipher(tfm);
	return ERR_PTR(err);
}