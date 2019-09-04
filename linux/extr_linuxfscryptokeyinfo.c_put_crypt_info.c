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
struct fscrypt_info {int /*<<< orphan*/  ci_essiv_tfm; int /*<<< orphan*/  ci_ctfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_cipher (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_skcipher (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscrypt_info_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct fscrypt_info*) ; 

__attribute__((used)) static void put_crypt_info(struct fscrypt_info *ci)
{
	if (!ci)
		return;

	crypto_free_skcipher(ci->ci_ctfm);
	crypto_free_cipher(ci->ci_essiv_tfm);
	kmem_cache_free(fscrypt_info_cachep, ci);
}