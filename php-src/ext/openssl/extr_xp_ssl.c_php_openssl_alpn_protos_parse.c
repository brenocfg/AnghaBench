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

/* Variables and functions */
 int /*<<< orphan*/  efree (unsigned char*) ; 
 unsigned char* emalloc (int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static unsigned char *php_openssl_alpn_protos_parse(unsigned short *outlen, const char *in) /* {{{ */
{
	size_t len;
	unsigned char *out;
	size_t i, start = 0;

	len = strlen(in);
	if (len >= 65535) {
		return NULL;
	}

	out = emalloc(strlen(in) + 1);

	for (i = 0; i <= len; ++i) {
		if (i == len || in[i] == ',') {
			if (i - start > 255) {
				efree(out);
				return NULL;
			}
			out[start] = i - start;
			start = i + 1;
		} else {
			out[i + 1] = in[i];
		}
	}

	*outlen = len + 1;

	return out;
}