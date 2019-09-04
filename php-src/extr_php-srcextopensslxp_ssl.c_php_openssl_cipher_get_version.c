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
typedef  int /*<<< orphan*/  SSL_CIPHER ;

/* Variables and functions */
 char* SSL_CIPHER_get_version (int /*<<< orphan*/  const*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static char *php_openssl_cipher_get_version(const SSL_CIPHER *c, char *buffer, size_t max_len) /* {{{ */
{
	const char *version = SSL_CIPHER_get_version(c);

	strncpy(buffer, version, max_len);
	if (max_len <= strlen(version)) {
		buffer[max_len - 1] = 0;
	}

	return buffer;
}