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

__attribute__((used)) static char *
shellquote(char *b, char const *s)
{
	*b++ = '\'';
	while (*s)
	{
		if (*s == '\'')
			*b++ = '\'', *b++ = '\\', *b++ = '\'';
		*b++ = *s++;
	}
	*b++ = '\'';
	return b;
}