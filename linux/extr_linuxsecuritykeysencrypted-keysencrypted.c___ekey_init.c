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
struct encrypted_key_payload {scalar_t__ datalen; scalar_t__ master_desc; scalar_t__ format; scalar_t__ payload_data; scalar_t__ decrypted_data; scalar_t__ iv; scalar_t__ encrypted_data; scalar_t__ payload_datalen; } ;
struct ecryptfs_auth_tok {int dummy; } ;

/* Variables and functions */
 scalar_t__ ecryptfs_get_auth_tok_key (struct ecryptfs_auth_tok*) ; 
 scalar_t__ ivsize ; 
 char const* key_format_default ; 
 int /*<<< orphan*/  key_format_ecryptfs ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,unsigned int) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 unsigned int strlen (char const*) ; 

__attribute__((used)) static void __ekey_init(struct encrypted_key_payload *epayload,
			const char *format, const char *master_desc,
			const char *datalen)
{
	unsigned int format_len;

	format_len = (!format) ? strlen(key_format_default) : strlen(format);
	epayload->format = epayload->payload_data + epayload->payload_datalen;
	epayload->master_desc = epayload->format + format_len + 1;
	epayload->datalen = epayload->master_desc + strlen(master_desc) + 1;
	epayload->iv = epayload->datalen + strlen(datalen) + 1;
	epayload->encrypted_data = epayload->iv + ivsize + 1;
	epayload->decrypted_data = epayload->payload_data;

	if (!format)
		memcpy(epayload->format, key_format_default, format_len);
	else {
		if (!strcmp(format, key_format_ecryptfs))
			epayload->decrypted_data =
				ecryptfs_get_auth_tok_key((struct ecryptfs_auth_tok *)epayload->payload_data);

		memcpy(epayload->format, format, format_len);
	}

	memcpy(epayload->master_desc, master_desc, strlen(master_desc));
	memcpy(epayload->datalen, datalen, strlen(datalen));
}