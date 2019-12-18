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
 scalar_t__ strcasecmp (char const*,char const*) ; 

__attribute__((used)) static int
lookup_value(const char **names, int size, const char *name)
{
	int value;

	for (value = 0; value < size; value++)
		if (names[value] && strcasecmp(names[value], name) == 0)
			return value;

	return -1;
}