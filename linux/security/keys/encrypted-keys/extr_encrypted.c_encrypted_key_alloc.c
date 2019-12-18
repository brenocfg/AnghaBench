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
struct key {int dummy; } ;
struct encrypted_key_payload {unsigned short payload_datalen; unsigned short decrypted_datalen; unsigned short datablob_len; } ;
struct ecryptfs_auth_tok {int dummy; } ;

/* Variables and functions */
 long ECRYPTFS_MAX_KEY_BYTES ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct encrypted_key_payload* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HASH_SIZE ; 
 unsigned short KEY_ENC32_PAYLOAD_LEN ; 
 long MAX_DATA_SIZE ; 
 long MIN_DATA_SIZE ; 
 int /*<<< orphan*/  blksize ; 
 unsigned int ivsize ; 
 char const* key_format_default ; 
 int /*<<< orphan*/  key_format_ecryptfs ; 
 int /*<<< orphan*/  key_format_enc32 ; 
 int key_payload_reserve (struct key*,scalar_t__) ; 
 int kstrtol (char const*,int,long*) ; 
 struct encrypted_key_payload* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned short) ; 
 unsigned int roundup (unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 unsigned int strlen (char const*) ; 

__attribute__((used)) static struct encrypted_key_payload *encrypted_key_alloc(struct key *key,
							 const char *format,
							 const char *master_desc,
							 const char *datalen)
{
	struct encrypted_key_payload *epayload = NULL;
	unsigned short datablob_len;
	unsigned short decrypted_datalen;
	unsigned short payload_datalen;
	unsigned int encrypted_datalen;
	unsigned int format_len;
	long dlen;
	int ret;

	ret = kstrtol(datalen, 10, &dlen);
	if (ret < 0 || dlen < MIN_DATA_SIZE || dlen > MAX_DATA_SIZE)
		return ERR_PTR(-EINVAL);

	format_len = (!format) ? strlen(key_format_default) : strlen(format);
	decrypted_datalen = dlen;
	payload_datalen = decrypted_datalen;
	if (format) {
		if (!strcmp(format, key_format_ecryptfs)) {
			if (dlen != ECRYPTFS_MAX_KEY_BYTES) {
				pr_err("encrypted_key: keylen for the ecryptfs format must be equal to %d bytes\n",
					ECRYPTFS_MAX_KEY_BYTES);
				return ERR_PTR(-EINVAL);
			}
			decrypted_datalen = ECRYPTFS_MAX_KEY_BYTES;
			payload_datalen = sizeof(struct ecryptfs_auth_tok);
		} else if (!strcmp(format, key_format_enc32)) {
			if (decrypted_datalen != KEY_ENC32_PAYLOAD_LEN) {
				pr_err("encrypted_key: enc32 key payload incorrect length: %d\n",
						decrypted_datalen);
				return ERR_PTR(-EINVAL);
			}
		}
	}

	encrypted_datalen = roundup(decrypted_datalen, blksize);

	datablob_len = format_len + 1 + strlen(master_desc) + 1
	    + strlen(datalen) + 1 + ivsize + 1 + encrypted_datalen;

	ret = key_payload_reserve(key, payload_datalen + datablob_len
				  + HASH_SIZE + 1);
	if (ret < 0)
		return ERR_PTR(ret);

	epayload = kzalloc(sizeof(*epayload) + payload_datalen +
			   datablob_len + HASH_SIZE + 1, GFP_KERNEL);
	if (!epayload)
		return ERR_PTR(-ENOMEM);

	epayload->payload_datalen = payload_datalen;
	epayload->decrypted_datalen = decrypted_datalen;
	epayload->datablob_len = datablob_len;
	return epayload;
}