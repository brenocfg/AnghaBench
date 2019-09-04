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
 scalar_t__ isspace (char const) ; 

__attribute__((used)) static int count_argc(const char *str)
{
	int count = 0;
	bool was_space;

	for (was_space = true; *str; str++) {
		if (isspace(*str)) {
			was_space = true;
		} else if (was_space) {
			was_space = false;
			count++;
		}
	}

	return count;
}