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
struct ubifs_mst_node {int dummy; } ;
struct ubifs_info {int /*<<< orphan*/  hash_tfm; } ;
struct ubifs_ch {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int UBIFS_MAX_HASH_LEN ; 
 scalar_t__ UBIFS_MST_NODE_SZ ; 
 int /*<<< orphan*/  crypto_shash_digest (TYPE_1__*,void const*,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_1__* shash ; 
 scalar_t__ ubifs_check_hash (struct ubifs_info const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mst_node_check_hash(const struct ubifs_info *c,
			       const struct ubifs_mst_node *mst,
			       const u8 *expected)
{
	u8 calc[UBIFS_MAX_HASH_LEN];
	const void *node = mst;

	SHASH_DESC_ON_STACK(shash, c->hash_tfm);

	shash->tfm = c->hash_tfm;

	crypto_shash_digest(shash, node + sizeof(struct ubifs_ch),
			    UBIFS_MST_NODE_SZ - sizeof(struct ubifs_ch), calc);

	if (ubifs_check_hash(c, expected, calc))
		return -EPERM;

	return 0;
}