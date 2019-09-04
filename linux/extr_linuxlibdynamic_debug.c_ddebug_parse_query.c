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
struct ddebug_query {char const* module; char const* function; char const* filename; char const* format; int /*<<< orphan*/  first_lineno; int /*<<< orphan*/  last_lineno; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int UNESCAPE_OCTAL ; 
 int UNESCAPE_SPACE ; 
 int UNESCAPE_SPECIAL ; 
 int check_set (char const**,char*,char*) ; 
 int /*<<< orphan*/  memset (struct ddebug_query*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parse_lineno (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  string_unescape_inplace (char*,int) ; 
 int /*<<< orphan*/  vpr_info_dq (struct ddebug_query*,char*) ; 

__attribute__((used)) static int ddebug_parse_query(char *words[], int nwords,
			struct ddebug_query *query, const char *modname)
{
	unsigned int i;
	int rc = 0;

	/* check we have an even number of words */
	if (nwords % 2 != 0) {
		pr_err("expecting pairs of match-spec <value>\n");
		return -EINVAL;
	}
	memset(query, 0, sizeof(*query));

	if (modname)
		/* support $modname.dyndbg=<multiple queries> */
		query->module = modname;

	for (i = 0; i < nwords; i += 2) {
		if (!strcmp(words[i], "func")) {
			rc = check_set(&query->function, words[i+1], "func");
		} else if (!strcmp(words[i], "file")) {
			rc = check_set(&query->filename, words[i+1], "file");
		} else if (!strcmp(words[i], "module")) {
			rc = check_set(&query->module, words[i+1], "module");
		} else if (!strcmp(words[i], "format")) {
			string_unescape_inplace(words[i+1], UNESCAPE_SPACE |
							    UNESCAPE_OCTAL |
							    UNESCAPE_SPECIAL);
			rc = check_set(&query->format, words[i+1], "format");
		} else if (!strcmp(words[i], "line")) {
			char *first = words[i+1];
			char *last = strchr(first, '-');
			if (query->first_lineno || query->last_lineno) {
				pr_err("match-spec: line used 2x\n");
				return -EINVAL;
			}
			if (last)
				*last++ = '\0';
			if (parse_lineno(first, &query->first_lineno) < 0)
				return -EINVAL;
			if (last) {
				/* range <first>-<last> */
				if (parse_lineno(last, &query->last_lineno) < 0)
					return -EINVAL;

				/* special case for last lineno not specified */
				if (query->last_lineno == 0)
					query->last_lineno = UINT_MAX;

				if (query->last_lineno < query->first_lineno) {
					pr_err("last-line:%d < 1st-line:%d\n",
						query->last_lineno,
						query->first_lineno);
					return -EINVAL;
				}
			} else {
				query->last_lineno = query->first_lineno;
			}
		} else {
			pr_err("unknown keyword \"%s\"\n", words[i]);
			return -EINVAL;
		}
		if (rc)
			return rc;
	}
	vpr_info_dq(query, "parsed");
	return 0;
}