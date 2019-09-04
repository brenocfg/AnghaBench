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
 unsigned long long SCAN_WILD_CARD ; 
 unsigned long long simple_strtoull (char*,char**,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int check_set(unsigned long long *val, char *src)
{
	char *last;

	if (strcmp(src, "-") == 0) {
		*val = SCAN_WILD_CARD;
	} else {
		/*
		 * Doesn't check for int overflow
		 */
		*val = simple_strtoull(src, &last, 0);
		if (*last != '\0')
			return 1;
	}
	return 0;
}