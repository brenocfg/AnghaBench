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
 scalar_t__ lowerit (char const) ; 

__attribute__((used)) static bool
itsabbr(const char *abbr, const char *word)
{
	if (lowerit(*abbr) != lowerit(*word))
		return false;
	++word;
	while (*++abbr != '\0')
		do
		{
			if (*word == '\0')
				return false;
		} while (lowerit(*word++) != lowerit(*abbr));
	return true;
}