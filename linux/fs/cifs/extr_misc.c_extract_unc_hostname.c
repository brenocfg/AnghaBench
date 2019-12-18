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

void extract_unc_hostname(const char *unc, const char **h, size_t *len)
{
	const char *end;

	/* skip initial slashes */
	while (*unc && (*unc == '\\' || *unc == '/'))
		unc++;

	end = unc;

	while (*end && !(*end == '\\' || *end == '/'))
		end++;

	*h = unc;
	*len = end - unc;
}