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
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static bool match_last_lsm(const char *list, const char *lsm)
{
	const char *last;

	if (WARN_ON(!list || !lsm))
		return false;
	last = strrchr(list, ',');
	if (last)
		/* Pass the comma, strcmp() will check for '\0' */
		last++;
	else
		last = list;
	return !strcmp(last, lsm);
}