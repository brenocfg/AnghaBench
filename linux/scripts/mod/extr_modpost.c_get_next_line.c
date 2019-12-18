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
 scalar_t__ isspace (char) ; 

char *get_next_line(unsigned long *pos, void *file, unsigned long size)
{
	static char line[4096];
	int skip = 1;
	size_t len = 0;
	signed char *p = (signed char *)file + *pos;
	char *s = line;

	for (; *pos < size ; (*pos)++) {
		if (skip && isspace(*p)) {
			p++;
			continue;
		}
		skip = 0;
		if (*p != '\n' && (*pos < size)) {
			len++;
			*s++ = *p++;
			if (len > 4095)
				break; /* Too long, stop */
		} else {
			/* End of string */
			*s = '\0';
			return line;
		}
	}
	/* End of buffer */
	return NULL;
}