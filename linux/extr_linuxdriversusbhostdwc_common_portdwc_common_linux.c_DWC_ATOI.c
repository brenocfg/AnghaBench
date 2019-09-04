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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  simple_strtol (char const*,char**,int /*<<< orphan*/ ) ; 

int DWC_ATOI(const char *str, int32_t *value)
{
	char *end = NULL;

	*value = simple_strtol(str, &end, 0);
	if (*end == '\0') {
		return 0;
	}

	return -1;
}