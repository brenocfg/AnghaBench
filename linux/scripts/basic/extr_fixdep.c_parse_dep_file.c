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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  is_ignored_file (char*,int) ; 
 int /*<<< orphan*/  parse_config_file (void*) ; 
 void* read_file (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  xprintf (char*,char const*,...) ; 

__attribute__((used)) static void parse_dep_file(char *m, const char *target)
{
	char *p;
	int is_last, is_target;
	int saw_any_target = 0;
	int is_first_dep = 0;
	void *buf;

	while (1) {
		/* Skip any "white space" */
		while (*m == ' ' || *m == '\\' || *m == '\n')
			m++;

		if (!*m)
			break;

		/* Find next "white space" */
		p = m;
		while (*p && *p != ' ' && *p != '\\' && *p != '\n')
			p++;
		is_last = (*p == '\0');
		/* Is the token we found a target name? */
		is_target = (*(p-1) == ':');
		/* Don't write any target names into the dependency file */
		if (is_target) {
			/* The /next/ file is the first dependency */
			is_first_dep = 1;
		} else if (!is_ignored_file(m, p - m)) {
			*p = '\0';

			/*
			 * Do not list the source file as dependency, so that
			 * kbuild is not confused if a .c file is rewritten
			 * into .S or vice versa. Storing it in source_* is
			 * needed for modpost to compute srcversions.
			 */
			if (is_first_dep) {
				/*
				 * If processing the concatenation of multiple
				 * dependency files, only process the first
				 * target name, which will be the original
				 * source name, and ignore any other target
				 * names, which will be intermediate temporary
				 * files.
				 */
				if (!saw_any_target) {
					saw_any_target = 1;
					xprintf("source_%s := %s\n\n",
						target, m);
					xprintf("deps_%s := \\\n", target);
				}
				is_first_dep = 0;
			} else {
				xprintf("  %s \\\n", m);
			}

			buf = read_file(m);
			parse_config_file(buf);
			free(buf);
		}

		if (is_last)
			break;

		/*
		 * Start searching for next token immediately after the first
		 * "whitespace" character that follows this token.
		 */
		m = p + 1;
	}

	if (!saw_any_target) {
		fprintf(stderr, "fixdep: parse error; no targets found\n");
		exit(1);
	}

	xprintf("\n%s: $(deps_%s)\n\n", target, target);
	xprintf("$(deps_%s):\n", target);
}