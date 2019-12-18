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
 int /*<<< orphan*/  PHAR_G (int /*<<< orphan*/ ) ; 
 char* hexChars ; 
 int /*<<< orphan*/  persist ; 
 scalar_t__ safe_pemalloc (size_t,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int phar_hex_str(const char *digest, size_t digest_len, char **signature) /* {{{ */
{
	int pos = -1;
	size_t len = 0;

	*signature = (char*)safe_pemalloc(digest_len, 2, 1, PHAR_G(persist));

	for (; len < digest_len; ++len) {
		(*signature)[++pos] = hexChars[((const unsigned char *)digest)[len] >> 4];
		(*signature)[++pos] = hexChars[((const unsigned char *)digest)[len] & 0x0F];
	}
	(*signature)[++pos] = '\0';
	return pos;
}