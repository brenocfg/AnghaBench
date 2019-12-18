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
struct ubifs_info {int hmac_desc_len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int crypto_memneq (int /*<<< orphan*/ *,void const*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int ubifs_node_calc_hmac (struct ubifs_info const*,void const*,int,int,int /*<<< orphan*/ *) ; 

int __ubifs_node_verify_hmac(const struct ubifs_info *c, const void *node,
			     int len, int ofs_hmac)
{
	int hmac_len = c->hmac_desc_len;
	u8 *hmac;
	int err;

	hmac = kmalloc(hmac_len, GFP_NOFS);
	if (!hmac)
		return -ENOMEM;

	err = ubifs_node_calc_hmac(c, node, len, ofs_hmac, hmac);
	if (err) {
		kfree(hmac);
		return err;
	}

	err = crypto_memneq(hmac, node + ofs_hmac, hmac_len);

	kfree(hmac);

	if (!err)
		return 0;

	return -EPERM;
}