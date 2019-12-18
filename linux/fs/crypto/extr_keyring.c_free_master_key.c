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
struct fscrypt_master_key {int /*<<< orphan*/  mk_users; int /*<<< orphan*/ * mk_mode_keys; int /*<<< orphan*/  mk_secret; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_free_skcipher (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct fscrypt_master_key*) ; 
 int /*<<< orphan*/  wipe_master_key_secret (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_master_key(struct fscrypt_master_key *mk)
{
	size_t i;

	wipe_master_key_secret(&mk->mk_secret);

	for (i = 0; i < ARRAY_SIZE(mk->mk_mode_keys); i++)
		crypto_free_skcipher(mk->mk_mode_keys[i]);

	key_put(mk->mk_users);
	kzfree(mk);
}