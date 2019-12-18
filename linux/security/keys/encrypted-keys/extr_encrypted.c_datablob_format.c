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
struct encrypted_key_payload {char* format; char* master_desc; char* datalen; int /*<<< orphan*/ * iv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* hex_byte_pack (char*,int /*<<< orphan*/ ) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,char*,char*,char*) ; 

__attribute__((used)) static char *datablob_format(struct encrypted_key_payload *epayload,
			     size_t asciiblob_len)
{
	char *ascii_buf, *bufp;
	u8 *iv = epayload->iv;
	int len;
	int i;

	ascii_buf = kmalloc(asciiblob_len + 1, GFP_KERNEL);
	if (!ascii_buf)
		goto out;

	ascii_buf[asciiblob_len] = '\0';

	/* copy datablob master_desc and datalen strings */
	len = sprintf(ascii_buf, "%s %s %s ", epayload->format,
		      epayload->master_desc, epayload->datalen);

	/* convert the hex encoded iv, encrypted-data and HMAC to ascii */
	bufp = &ascii_buf[len];
	for (i = 0; i < (asciiblob_len - len) / 2; i++)
		bufp = hex_byte_pack(bufp, iv[i]);
out:
	return ascii_buf;
}