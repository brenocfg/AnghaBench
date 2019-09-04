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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ESCAPE_HEX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 size_t string_escape_mem (char const*,size_t,char*,size_t,int const,char const*) ; 
 size_t strlen (char const*) ; 

char *kstrdup_quotable(const char *src, gfp_t gfp)
{
	size_t slen, dlen;
	char *dst;
	const int flags = ESCAPE_HEX;
	const char esc[] = "\f\n\r\t\v\a\e\\\"";

	if (!src)
		return NULL;
	slen = strlen(src);

	dlen = string_escape_mem(src, slen, NULL, 0, flags, esc);
	dst = kmalloc(dlen + 1, gfp);
	if (!dst)
		return NULL;

	WARN_ON(string_escape_mem(src, slen, dst, dlen, flags, esc) != dlen);
	dst[dlen] = '\0';

	return dst;
}