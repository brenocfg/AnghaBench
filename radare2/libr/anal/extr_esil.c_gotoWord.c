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

__attribute__((used)) static const char *gotoWord(const char *str, int n) {
	const char *ostr = str;
	int count = 0;
	while (*str) {
		if (count == n) {
			return ostr;
		}
		str++;
		if (*str == ',') {
			ostr = str + 1;
			count++;
		}
	}
	return NULL;
}