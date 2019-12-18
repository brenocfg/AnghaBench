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
typedef  scalar_t__ pg_wchar ;

/* Variables and functions */

int
pg_char_and_wchar_strncmp(const char *s1, const pg_wchar *s2, size_t n)
{
	if (n == 0)
		return 0;
	do
	{
		if ((pg_wchar) ((unsigned char) *s1) != *s2++)
			return ((pg_wchar) ((unsigned char) *s1) - *(s2 - 1));
		if (*s1++ == 0)
			break;
	} while (--n != 0);
	return 0;
}