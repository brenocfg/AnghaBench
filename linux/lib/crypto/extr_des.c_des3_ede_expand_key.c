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
typedef  int /*<<< orphan*/  u32 ;
struct des3_ede_ctx {int /*<<< orphan*/ * expkey; } ;

/* Variables and functions */
 unsigned int DES3_EDE_KEY_SIZE ; 
 int /*<<< orphan*/  DES_EXPKEY_WORDS ; 
 int /*<<< orphan*/  DES_KEY_SIZE ; 
 int EINVAL ; 
 int ENOKEY ; 
 int des3_ede_verify_key (int /*<<< orphan*/  const*,unsigned int,int) ; 
 int /*<<< orphan*/  des_ekey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dkey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int des3_ede_expand_key(struct des3_ede_ctx *ctx, const u8 *key,
			unsigned int keylen)
{
	u32 *pe = ctx->expkey;
	int err;

	if (keylen != DES3_EDE_KEY_SIZE)
		return -EINVAL;

	err = des3_ede_verify_key(key, keylen, true);
	if (err && err != -ENOKEY)
		return err;

	des_ekey(pe, key); pe += DES_EXPKEY_WORDS; key += DES_KEY_SIZE;
	dkey(pe, key); pe += DES_EXPKEY_WORDS; key += DES_KEY_SIZE;
	des_ekey(pe, key);

	return err;
}