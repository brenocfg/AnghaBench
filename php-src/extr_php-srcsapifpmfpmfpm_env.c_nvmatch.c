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

__attribute__((used)) static char * nvmatch(char *s1, char *s2) /* {{{ */
{
	while(*s1 == *s2++)
	{
		if(*s1++ == '=') {
			return s2;
		}
	}
	if(*s1 == '\0' && *(s2-1) == '=') {
		return s2;
	}
	return NULL;
}