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
struct encrypted_key_payload {int datablob_len; int /*<<< orphan*/ * format; } ;
typedef  int /*<<< orphan*/  derived_key ;

/* Variables and functions */
 int /*<<< orphan*/  AUTH_KEY ; 
 int HASH_SIZE ; 
 int calc_hmac (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dump_hmac (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int get_derived_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  memzero_explicit (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int datablob_hmac_append(struct encrypted_key_payload *epayload,
				const u8 *master_key, size_t master_keylen)
{
	u8 derived_key[HASH_SIZE];
	u8 *digest;
	int ret;

	ret = get_derived_key(derived_key, AUTH_KEY, master_key, master_keylen);
	if (ret < 0)
		goto out;

	digest = epayload->format + epayload->datablob_len;
	ret = calc_hmac(digest, derived_key, sizeof derived_key,
			epayload->format, epayload->datablob_len);
	if (!ret)
		dump_hmac(NULL, digest, HASH_SIZE);
out:
	memzero_explicit(derived_key, sizeof(derived_key));
	return ret;
}