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
struct fscrypt_direct_key {int /*<<< orphan*/  dk_node; int /*<<< orphan*/  dk_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_direct_key (struct fscrypt_direct_key*) ; 
 int /*<<< orphan*/  fscrypt_direct_keys_lock ; 
 int /*<<< orphan*/  hash_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void fscrypt_put_direct_key(struct fscrypt_direct_key *dk)
{
	if (!refcount_dec_and_lock(&dk->dk_refcount, &fscrypt_direct_keys_lock))
		return;
	hash_del(&dk->dk_node);
	spin_unlock(&fscrypt_direct_keys_lock);

	free_direct_key(dk);
}