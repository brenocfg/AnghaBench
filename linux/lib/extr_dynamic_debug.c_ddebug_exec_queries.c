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
 int ddebug_exec_query (char*,char const*) ; 
 char* skip_spaces (char*) ; 
 char* strpbrk (char*,char*) ; 
 int /*<<< orphan*/  vpr_info (char*,int,...) ; 

__attribute__((used)) static int ddebug_exec_queries(char *query, const char *modname)
{
	char *split;
	int i, errs = 0, exitcode = 0, rc, nfound = 0;

	for (i = 0; query; query = split) {
		split = strpbrk(query, ";\n");
		if (split)
			*split++ = '\0';

		query = skip_spaces(query);
		if (!query || !*query || *query == '#')
			continue;

		vpr_info("query %d: \"%s\"\n", i, query);

		rc = ddebug_exec_query(query, modname);
		if (rc < 0) {
			errs++;
			exitcode = rc;
		} else {
			nfound += rc;
		}
		i++;
	}
	vpr_info("processed %d queries, with %d matches, %d errs\n",
		 i, nfound, errs);

	if (exitcode)
		return exitcode;
	return nfound;
}