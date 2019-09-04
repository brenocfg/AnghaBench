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
 scalar_t__ strchr (char*,char) ; 
 int strlen (char*) ; 

__attribute__((used)) static int check_modifier(char *str)
{
	char *p = str;

	/* The sizeof includes 0 byte as well. */
	if (strlen(str) > (sizeof("ukhGHpppPSDIW") - 1))
		return -1;

	while (*p) {
		if (*p != 'p' && strchr(p + 1, *p))
			return -1;
		p++;
	}

	return 0;
}