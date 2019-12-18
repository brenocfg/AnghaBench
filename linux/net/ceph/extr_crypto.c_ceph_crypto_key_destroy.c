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
struct ceph_crypto_key {int /*<<< orphan*/ * tfm; int /*<<< orphan*/ * key; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_sync_skcipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void ceph_crypto_key_destroy(struct ceph_crypto_key *key)
{
	if (key) {
		kfree(key->key);
		key->key = NULL;
		if (key->tfm) {
			crypto_free_sync_skcipher(key->tfm);
			key->tfm = NULL;
		}
	}
}