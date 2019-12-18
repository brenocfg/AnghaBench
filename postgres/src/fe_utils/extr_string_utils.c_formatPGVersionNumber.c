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
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int,...) ; 

char *
formatPGVersionNumber(int version_number, bool include_minor,
					  char *buf, size_t buflen)
{
	if (version_number >= 100000)
	{
		/* New two-part style */
		if (include_minor)
			snprintf(buf, buflen, "%d.%d", version_number / 10000,
					 version_number % 10000);
		else
			snprintf(buf, buflen, "%d", version_number / 10000);
	}
	else
	{
		/* Old three-part style */
		if (include_minor)
			snprintf(buf, buflen, "%d.%d.%d", version_number / 10000,
					 (version_number / 100) % 100,
					 version_number % 100);
		else
			snprintf(buf, buflen, "%d.%d", version_number / 10000,
					 (version_number / 100) % 100);
	}
	return buf;
}