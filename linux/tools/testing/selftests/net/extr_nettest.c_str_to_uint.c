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
 scalar_t__ ERANGE ; 
 scalar_t__ errno ; 
 scalar_t__ strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int str_to_uint(const char *str, int min, int max, unsigned int *value)
{
	int number;
	char *end;

	errno = 0;
	number = (unsigned int) strtoul(str, &end, 0);

	/* entire string should be consumed by conversion
	 * and value should be between min and max
	 */
	if (((*end == '\0') || (*end == '\n')) && (end != str) &&
	    (errno != ERANGE) && (min <= number) && (number <= max)) {
		*value = number;
		return 0;
	}

	return -1;
}