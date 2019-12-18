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
 char* strpbrk (char*,char const*) ; 

char *strpbrk_esc(char *str, const char *stopset)
{
	char *ptr;

	do {
		ptr = strpbrk(str, stopset);
		if (ptr == str ||
		    (ptr == str + 1 && *(ptr - 1) != '\\'))
			break;
		str = ptr + 1;
	} while (ptr && *(ptr - 1) == '\\' && *(ptr - 2) != '\\');

	return ptr;
}