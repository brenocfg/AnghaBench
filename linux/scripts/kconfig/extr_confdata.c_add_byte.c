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
 int LINE_GROWTH ; 
 char* xrealloc (char*,size_t) ; 

__attribute__((used)) static int add_byte(int c, char **lineptr, size_t slen, size_t *n)
{
	char *nline;
	size_t new_size = slen + 1;
	if (new_size > *n) {
		new_size += LINE_GROWTH - 1;
		new_size *= 2;
		nline = xrealloc(*lineptr, new_size);
		if (!nline)
			return -1;

		*lineptr = nline;
		*n = new_size;
	}

	(*lineptr)[slen] = c;

	return 0;
}