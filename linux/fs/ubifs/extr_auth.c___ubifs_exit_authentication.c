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
struct ubifs_info {int /*<<< orphan*/  log_hash; int /*<<< orphan*/  hash_tfm; int /*<<< orphan*/  hmac_tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_authenticated (struct ubifs_info*) ; 

void __ubifs_exit_authentication(struct ubifs_info *c)
{
	if (!ubifs_authenticated(c))
		return;

	crypto_free_shash(c->hmac_tfm);
	crypto_free_shash(c->hash_tfm);
	kfree(c->log_hash);
}