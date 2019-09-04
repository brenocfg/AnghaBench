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
struct crypto_cipher {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct crypto_cipher*) ; 
 int PTR_ERR (struct crypto_cipher*) ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 struct crypto_cipher* crypto_alloc_cipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_cipher_encrypt_one (struct crypto_cipher*,unsigned char*,unsigned char const*) ; 
 int /*<<< orphan*/  crypto_cipher_setkey (struct crypto_cipher*,unsigned char*,int) ; 
 int /*<<< orphan*/  crypto_free_cipher (struct crypto_cipher*) ; 
 int /*<<< orphan*/  str_to_key (unsigned char*,unsigned char*) ; 

__attribute__((used)) static int
smbhash(unsigned char *out, const unsigned char *in, unsigned char *key)
{
	unsigned char key2[8];
	struct crypto_cipher *tfm_des;

	str_to_key(key, key2);

	tfm_des = crypto_alloc_cipher("des", 0, 0);
	if (IS_ERR(tfm_des)) {
		cifs_dbg(VFS, "could not allocate des crypto API\n");
		return PTR_ERR(tfm_des);
	}

	crypto_cipher_setkey(tfm_des, key2, 8);
	crypto_cipher_encrypt_one(tfm_des, out, in);
	crypto_free_cipher(tfm_des);

	return 0;
}