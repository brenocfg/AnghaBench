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
struct encrypted_key_payload {int /*<<< orphan*/  decrypted_datalen; int /*<<< orphan*/  decrypted_data; int /*<<< orphan*/  iv; scalar_t__ payload_data; } ;
struct ecryptfs_auth_tok {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ekey_init (struct encrypted_key_payload*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  ecryptfs_fill_auth_tok (struct ecryptfs_auth_tok*,char const*) ; 
 int encrypted_key_decrypt (struct encrypted_key_payload*,char const*,char const*) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ivsize ; 
 int /*<<< orphan*/  key_format_ecryptfs ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int valid_ecryptfs_desc (char const*) ; 

__attribute__((used)) static int encrypted_init(struct encrypted_key_payload *epayload,
			  const char *key_desc, const char *format,
			  const char *master_desc, const char *datalen,
			  const char *hex_encoded_iv)
{
	int ret = 0;

	if (format && !strcmp(format, key_format_ecryptfs)) {
		ret = valid_ecryptfs_desc(key_desc);
		if (ret < 0)
			return ret;

		ecryptfs_fill_auth_tok((struct ecryptfs_auth_tok *)epayload->payload_data,
				       key_desc);
	}

	__ekey_init(epayload, format, master_desc, datalen);
	if (!hex_encoded_iv) {
		get_random_bytes(epayload->iv, ivsize);

		get_random_bytes(epayload->decrypted_data,
				 epayload->decrypted_datalen);
	} else
		ret = encrypted_key_decrypt(epayload, format, hex_encoded_iv);
	return ret;
}