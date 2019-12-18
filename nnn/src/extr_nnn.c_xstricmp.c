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
typedef  scalar_t__ ll ;

/* Variables and functions */
 int strcasecmp (char const* const,char const* const) ; 
 int strcoll (char const* const,char const* const) ; 
 scalar_t__ strtoll (char const* const,char**,int) ; 

__attribute__((used)) static int xstricmp(const char * const s1, const char * const s2)
{
	char *p1, *p2;

	ll v1 = strtoll(s1, &p1, 10);
	ll v2 = strtoll(s2, &p2, 10);

	/* Check if at least 1 string is numeric */
	if (s1 != p1 || s2 != p2) {
		/* Handle both pure numeric */
		if (s1 != p1 && s2 != p2) {
			if (v2 > v1)
				return -1;

			if (v1 > v2)
				return 1;
		}

		/* Only first string non-numeric */
		if (s1 == p1)
			return 1;

		/* Only second string non-numeric */
		if (s2 == p2)
			return -1;
	}

	/* Handle 1. all non-numeric and 2. both same numeric value cases */
#ifndef NOLOCALE
	return strcoll(s1, s2);
#else
	return strcasecmp(s1, s2);
#endif
}