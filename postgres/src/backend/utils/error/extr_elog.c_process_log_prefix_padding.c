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

__attribute__((used)) static const char *
process_log_prefix_padding(const char *p, int *ppadding)
{
	int			paddingsign = 1;
	int			padding = 0;

	if (*p == '-')
	{
		p++;

		if (*p == '\0')			/* Did the buf end in %- ? */
			return NULL;
		paddingsign = -1;
	}

	/* generate an int version of the numerical string */
	while (*p >= '0' && *p <= '9')
		padding = padding * 10 + (*p++ - '0');

	/* format is invalid if it ends with the padding number */
	if (*p == '\0')
		return NULL;

	padding *= paddingsign;
	*ppadding = padding;
	return p;
}