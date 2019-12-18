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
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int /*<<< orphan*/ ) ; 
 char* strstr (char const*,char*) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static bool pmu_uncore_alias_match(const char *pmu_name, const char *name)
{
	char *tmp = NULL, *tok, *str;
	bool res;

	str = strdup(pmu_name);
	if (!str)
		return false;

	/*
	 * uncore alias may be from different PMU with common prefix
	 */
	tok = strtok_r(str, ",", &tmp);
	if (strncmp(pmu_name, tok, strlen(tok))) {
		res = false;
		goto out;
	}

	/*
	 * Match more complex aliases where the alias name is a comma-delimited
	 * list of tokens, orderly contained in the matching PMU name.
	 *
	 * Example: For alias "socket,pmuname" and PMU "socketX_pmunameY", we
	 *	    match "socket" in "socketX_pmunameY" and then "pmuname" in
	 *	    "pmunameY".
	 */
	for (; tok; name += strlen(tok), tok = strtok_r(NULL, ",", &tmp)) {
		name = strstr(name, tok);
		if (!name) {
			res = false;
			goto out;
		}
	}

	res = true;
out:
	free(str);
	return res;
}