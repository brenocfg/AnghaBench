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
struct ubifs_info {int /*<<< orphan*/  hash_len; int /*<<< orphan*/  hmac_tfm; } ;
struct TYPE_4__ {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int crypto_shash_digest (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* shash ; 

__attribute__((used)) static int ubifs_hash_calc_hmac(const struct ubifs_info *c, const u8 *hash,
				 u8 *hmac)
{
	SHASH_DESC_ON_STACK(shash, c->hmac_tfm);
	int err;

	shash->tfm = c->hmac_tfm;

	err = crypto_shash_digest(shash, hash, c->hash_len, hmac);
	if (err < 0)
		return err;
	return 0;
}