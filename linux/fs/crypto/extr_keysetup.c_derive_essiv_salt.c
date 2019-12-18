#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct crypto_shash {int dummy; } ;
struct TYPE_4__ {struct crypto_shash* tfm; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOPKG ; 
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 int PTR_ERR (struct crypto_shash*) ; 
 struct crypto_shash* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_1__*,struct crypto_shash*) ; 
 struct crypto_shash* cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct crypto_shash*) ; 
 struct crypto_shash* crypto_alloc_shash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_shash (struct crypto_shash*) ; 
 int crypto_shash_digest (TYPE_1__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* desc ; 
 int /*<<< orphan*/  essiv_hash_tfm ; 
 int /*<<< orphan*/  fscrypt_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fscrypt_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int derive_essiv_salt(const u8 *key, int keysize, u8 *salt)
{
	struct crypto_shash *tfm = READ_ONCE(essiv_hash_tfm);

	/* init hash transform on demand */
	if (unlikely(!tfm)) {
		struct crypto_shash *prev_tfm;

		tfm = crypto_alloc_shash("sha256", 0, 0);
		if (IS_ERR(tfm)) {
			if (PTR_ERR(tfm) == -ENOENT) {
				fscrypt_warn(NULL,
					     "Missing crypto API support for SHA-256");
				return -ENOPKG;
			}
			fscrypt_err(NULL,
				    "Error allocating SHA-256 transform: %ld",
				    PTR_ERR(tfm));
			return PTR_ERR(tfm);
		}
		prev_tfm = cmpxchg(&essiv_hash_tfm, NULL, tfm);
		if (prev_tfm) {
			crypto_free_shash(tfm);
			tfm = prev_tfm;
		}
	}

	{
		SHASH_DESC_ON_STACK(desc, tfm);
		desc->tfm = tfm;

		return crypto_shash_digest(desc, key, keysize, salt);
	}
}