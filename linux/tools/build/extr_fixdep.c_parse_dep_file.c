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
 int PATH_MAX ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* target ; 

__attribute__((used)) static void parse_dep_file(void *map, size_t len)
{
	char *m = map;
	char *end = m + len;
	char *p;
	char s[PATH_MAX];
	int is_target, has_target = 0;
	int saw_any_target = 0;
	int is_first_dep = 0;

	while (m < end) {
		/* Skip any "white space" */
		while (m < end && (*m == ' ' || *m == '\\' || *m == '\n'))
			m++;
		/* Find next "white space" */
		p = m;
		while (p < end && *p != ' ' && *p != '\\' && *p != '\n')
			p++;
		/* Is the token we found a target name? */
		is_target = (*(p-1) == ':');
		/* Don't write any target names into the dependency file */
		if (is_target) {
			/* The /next/ file is the first dependency */
			is_first_dep = 1;
			has_target = 1;
		} else if (has_target) {
			/* Save this token/filename */
			memcpy(s, m, p-m);
			s[p - m] = 0;

			/*
			 * Do not list the source file as dependency,
			 * so that kbuild is not confused if a .c file
			 * is rewritten into .S or vice versa. Storing
			 * it in source_* is needed for modpost to
			 * compute srcversions.
			 */
			if (is_first_dep) {
				/*
				 * If processing the concatenation of
				 * multiple dependency files, only
				 * process the first target name, which
				 * will be the original source name,
				 * and ignore any other target names,
				 * which will be intermediate temporary
				 * files.
				 */
				if (!saw_any_target) {
					saw_any_target = 1;
					printf("source_%s := %s\n\n",
						target, s);
					printf("deps_%s := \\\n",
						target);
				}
				is_first_dep = 0;
			} else
				printf("  %s \\\n", s);
		}
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

	printf("\n%s: $(deps_%s)\n\n", target, target);
	printf("$(deps_%s):\n", target);
}