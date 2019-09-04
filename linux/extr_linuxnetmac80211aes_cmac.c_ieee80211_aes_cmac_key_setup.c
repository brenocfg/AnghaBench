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
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct crypto_shash*) ; 
 struct crypto_shash* crypto_alloc_shash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_shash_setkey (struct crypto_shash*,int /*<<< orphan*/  const*,size_t) ; 

struct crypto_shash *ieee80211_aes_cmac_key_setup(const u8 key[],
						  size_t key_len)
{
	struct crypto_shash *tfm;

	tfm = crypto_alloc_shash("cmac(aes)", 0, 0);
	if (!IS_ERR(tfm))
		crypto_shash_setkey(tfm, key, key_len);

	return tfm;
}