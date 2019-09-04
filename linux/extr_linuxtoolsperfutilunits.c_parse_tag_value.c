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
struct parse_tag {unsigned long mult; scalar_t__ tag; } ;

/* Variables and functions */
 unsigned long ULONG_MAX ; 
 char* strchr (char const*,scalar_t__) ; 
 unsigned long strtoul (char const*,char**,int) ; 

unsigned long parse_tag_value(const char *str, struct parse_tag *tags)
{
	struct parse_tag *i = tags;

	while (i->tag) {
		char *s = strchr(str, i->tag);

		if (s) {
			unsigned long int value;
			char *endptr;

			value = strtoul(str, &endptr, 10);
			if (s != endptr)
				break;

			if (value > ULONG_MAX / i->mult)
				break;
			value *= i->mult;
			return value;
		}
		i++;
	}

	return (unsigned long) -1;
}