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
 int /*<<< orphan*/  r_str_casecmp (char*,char const*) ; 

__attribute__((used)) static int get_mem_option(char *token) {
	// values 4, 8, 12, are unused. XXX to adjust
	const char *options[] = {"sy", "st", "ld", "xxx", "ish", "ishst",
	                         "ishld", "xxx", "nsh", "nshst", "nshld",
	                         "xxx", "osh", "oshst", "oshld", NULL};
	int i = 0;
	while (options[i]) {
		if (!r_str_casecmp (token, options[i])) {
			return 15 - i;
		}
		i++;
	}
	return -1;
}