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
struct ubifs_info {int /*<<< orphan*/  hash_tfm; } ;
struct ubifs_ch {int /*<<< orphan*/  len; } ;
struct TYPE_4__ {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int crypto_shash_digest (TYPE_1__*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_1__* shash ; 

int __ubifs_node_calc_hash(const struct ubifs_info *c, const void *node,
			    u8 *hash)
{
	const struct ubifs_ch *ch = node;
	SHASH_DESC_ON_STACK(shash, c->hash_tfm);
	int err;

	shash->tfm = c->hash_tfm;

	err = crypto_shash_digest(shash, node, le32_to_cpu(ch->len), hash);
	if (err < 0)
		return err;
	return 0;
}