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
 int crypto_shash_digest (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* hmac_desc ; 

__attribute__((used)) static int authenticate_sleb_hmac(struct ubifs_info *c, u8 *hash, u8 *hmac)
{
	SHASH_DESC_ON_STACK(hmac_desc, c->hmac_tfm);

	hmac_desc->tfm = c->hmac_tfm;

	return crypto_shash_digest(hmac_desc, hash, c->hash_len, hmac);
}