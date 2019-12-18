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
 int tolower (char const) ; 

int
nn_strncasecmp(const char *a, const char *b, size_t len)
{
	int rv;
	size_t count;
	for (count = 0; count < len; count++) {
		if ((*a == 0) && (*b == 0)) {
			return (0);
		}
		if ((rv = tolower(*a) - tolower(*b)) != 0) {
			return (rv);
		}
		a++;
		b++;
	}
	return (0);
}