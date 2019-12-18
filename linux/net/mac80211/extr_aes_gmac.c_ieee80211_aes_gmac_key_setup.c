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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_ASYNC ; 
 struct crypto_aead* ERR_PTR (int) ; 
 int /*<<< orphan*/  GMAC_MIC_LEN ; 
 scalar_t__ IS_ERR (struct crypto_aead*) ; 
 int crypto_aead_setauthsize (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 int crypto_aead_setkey (struct crypto_aead*,int /*<<< orphan*/  const*,size_t) ; 
 struct crypto_aead* crypto_alloc_aead (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_aead (struct crypto_aead*) ; 

struct crypto_aead *ieee80211_aes_gmac_key_setup(const u8 key[],
						 size_t key_len)
{
	struct crypto_aead *tfm;
	int err;

	tfm = crypto_alloc_aead("gcm(aes)", 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(tfm))
		return tfm;

	err = crypto_aead_setkey(tfm, key, key_len);
	if (!err)
		err = crypto_aead_setauthsize(tfm, GMAC_MIC_LEN);
	if (!err)
		return tfm;

	crypto_free_aead(tfm);
	return ERR_PTR(err);
}