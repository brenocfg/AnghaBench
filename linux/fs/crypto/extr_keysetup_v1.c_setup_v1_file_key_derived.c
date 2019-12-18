#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct fscrypt_info {TYPE_1__* ci_mode; int /*<<< orphan*/  ci_nonce; } ;
struct TYPE_2__ {int /*<<< orphan*/  keysize; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int derive_key_aes (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fscrypt_set_derived_key (struct fscrypt_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int setup_v1_file_key_derived(struct fscrypt_info *ci,
				     const u8 *raw_master_key)
{
	u8 *derived_key;
	int err;

	/*
	 * This cannot be a stack buffer because it will be passed to the
	 * scatterlist crypto API during derive_key_aes().
	 */
	derived_key = kmalloc(ci->ci_mode->keysize, GFP_NOFS);
	if (!derived_key)
		return -ENOMEM;

	err = derive_key_aes(raw_master_key, ci->ci_nonce,
			     derived_key, ci->ci_mode->keysize);
	if (err)
		goto out;

	err = fscrypt_set_derived_key(ci, derived_key);
out:
	kzfree(derived_key);
	return err;
}