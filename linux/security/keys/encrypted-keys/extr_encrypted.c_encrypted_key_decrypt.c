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
struct key {int /*<<< orphan*/  sem; } ;
struct encrypted_key_payload {int datablob_len; int /*<<< orphan*/ * format; int /*<<< orphan*/ * encrypted_data; int /*<<< orphan*/ * iv; int /*<<< orphan*/  decrypted_datalen; } ;
typedef  int /*<<< orphan*/  derived_key ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ENC_KEY ; 
 int HASH_SIZE ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  blksize ; 
 int datablob_hmac_verify (struct encrypted_key_payload*,char const*,int /*<<< orphan*/  const*,size_t) ; 
 int derived_key_decrypt (struct encrypted_key_payload*,int /*<<< orphan*/ *,int) ; 
 int get_derived_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int hex2bin (int /*<<< orphan*/ *,char const*,int) ; 
 int ivsize ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  memzero_explicit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct key* request_master_key (struct encrypted_key_payload*,int /*<<< orphan*/  const**,size_t*) ; 
 unsigned int roundup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int encrypted_key_decrypt(struct encrypted_key_payload *epayload,
				 const char *format, const char *hex_encoded_iv)
{
	struct key *mkey;
	u8 derived_key[HASH_SIZE];
	const u8 *master_key;
	u8 *hmac;
	const char *hex_encoded_data;
	unsigned int encrypted_datalen;
	size_t master_keylen;
	size_t asciilen;
	int ret;

	encrypted_datalen = roundup(epayload->decrypted_datalen, blksize);
	asciilen = (ivsize + 1 + encrypted_datalen + HASH_SIZE) * 2;
	if (strlen(hex_encoded_iv) != asciilen)
		return -EINVAL;

	hex_encoded_data = hex_encoded_iv + (2 * ivsize) + 2;
	ret = hex2bin(epayload->iv, hex_encoded_iv, ivsize);
	if (ret < 0)
		return -EINVAL;
	ret = hex2bin(epayload->encrypted_data, hex_encoded_data,
		      encrypted_datalen);
	if (ret < 0)
		return -EINVAL;

	hmac = epayload->format + epayload->datablob_len;
	ret = hex2bin(hmac, hex_encoded_data + (encrypted_datalen * 2),
		      HASH_SIZE);
	if (ret < 0)
		return -EINVAL;

	mkey = request_master_key(epayload, &master_key, &master_keylen);
	if (IS_ERR(mkey))
		return PTR_ERR(mkey);

	ret = datablob_hmac_verify(epayload, format, master_key, master_keylen);
	if (ret < 0) {
		pr_err("encrypted_key: bad hmac (%d)\n", ret);
		goto out;
	}

	ret = get_derived_key(derived_key, ENC_KEY, master_key, master_keylen);
	if (ret < 0)
		goto out;

	ret = derived_key_decrypt(epayload, derived_key, sizeof derived_key);
	if (ret < 0)
		pr_err("encrypted_key: failed to decrypt key (%d)\n", ret);
out:
	up_read(&mkey->sem);
	key_put(mkey);
	memzero_explicit(derived_key, sizeof(derived_key));
	return ret;
}