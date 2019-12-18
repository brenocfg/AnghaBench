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
 int /*<<< orphan*/  escape_hex (unsigned char,char**,char*) ; 
 int /*<<< orphan*/  escape_passthrough (unsigned char,char**,char*) ; 
 int /*<<< orphan*/  isascii (unsigned char) ; 
 int /*<<< orphan*/  isprint (unsigned char) ; 

int string_escape_mem_ascii(const char *src, size_t isz, char *dst,
					size_t osz)
{
	char *p = dst;
	char *end = p + osz;

	while (isz--) {
		unsigned char c = *src++;

		if (!isprint(c) || !isascii(c) || c == '"' || c == '\\')
			escape_hex(c, &p, end);
		else
			escape_passthrough(c, &p, end);
	}

	return p - dst;
}