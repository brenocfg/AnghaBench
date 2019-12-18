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
 int atoi (char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int getIndexFromLogString(const char *s) {
	int len = strlen (s);
	const char *m = s + len;
	int nlctr = 2;
	const char *nl = NULL;
	while (m > s) {
		if (*m == '\n') {
			nl = m;
			if (--nlctr < 1) {
				return atoi (m + 1);
			}
		}
		m--;
	}
		return atoi (nl?nl + 1: s);
	return -1;
}