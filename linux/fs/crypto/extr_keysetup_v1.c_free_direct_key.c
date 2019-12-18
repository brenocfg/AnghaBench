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
struct fscrypt_direct_key {int /*<<< orphan*/  dk_ctfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_skcipher (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct fscrypt_direct_key*) ; 

__attribute__((used)) static void free_direct_key(struct fscrypt_direct_key *dk)
{
	if (dk) {
		crypto_free_skcipher(dk->dk_ctfm);
		kzfree(dk);
	}
}