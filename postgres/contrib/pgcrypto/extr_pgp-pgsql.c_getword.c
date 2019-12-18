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
getword(char *p, char **res_p, int *res_len)
{
	/* whitespace at start */
	while (*p && (*p == ' ' || *p == '\t' || *p == '\n'))
		p++;

	/* word data */
	*res_p = p;
	if (*p == '=' || *p == ',')
		p++;
	else
		while (*p && !(*p == ' ' || *p == '\t' || *p == '\n'
					   || *p == '=' || *p == ','))
			p++;

	/* word end */
	*res_len = p - *res_p;

	/* whitespace at end */
	while (*p && (*p == ' ' || *p == '\t' || *p == '\n'))
		p++;

	return p;
}