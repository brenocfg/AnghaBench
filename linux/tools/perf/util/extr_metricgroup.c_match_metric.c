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
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 char* strcasestr (char const*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static bool match_metric(const char *n, const char *list)
{
	int len;
	char *m;

	if (!list)
		return false;
	if (!strcmp(list, "all"))
		return true;
	if (!n)
		return !strcasecmp(list, "No_group");
	len = strlen(list);
	m = strcasestr(n, list);
	if (!m)
		return false;
	if ((m == n || m[-1] == ';' || m[-1] == ' ') &&
	    (m[len] == 0 || m[len] == ';'))
		return true;
	return false;
}