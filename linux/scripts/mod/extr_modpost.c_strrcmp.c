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
 int memcmp (char const*,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int strrcmp(const char *s, const char *sub)
{
	int slen, sublen;

	if (!s || !sub)
		return 1;

	slen = strlen(s);
	sublen = strlen(sub);

	if ((slen == 0) || (sublen == 0))
		return 1;

	if (sublen > slen)
		return 1;

	return memcmp(s + slen - sublen, sub, sublen);
}