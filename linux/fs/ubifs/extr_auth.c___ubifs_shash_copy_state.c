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
struct ubifs_info {int dummy; } ;
struct shash_desc {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  crypto_shash_descsize (int /*<<< orphan*/ ) ; 
 int crypto_shash_export (struct shash_desc*,int /*<<< orphan*/ *) ; 
 int crypto_shash_import (struct shash_desc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __ubifs_shash_copy_state(const struct ubifs_info *c, struct shash_desc *src,
			     struct shash_desc *target)
{
	u8 *state;
	int err;

	state = kmalloc(crypto_shash_descsize(src->tfm), GFP_NOFS);
	if (!state)
		return -ENOMEM;

	err = crypto_shash_export(src, state);
	if (err)
		goto out;

	err = crypto_shash_import(target, state);

out:
	kfree(state);

	return err;
}