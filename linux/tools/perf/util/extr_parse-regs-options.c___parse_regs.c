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
typedef  int uint64_t ;
struct sample_reg {char* name; int mask; } ;
struct option {scalar_t__ value; } ;

/* Variables and functions */
 int arch__intr_reg_mask () ; 
 int arch__user_reg_mask () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct sample_reg* sample_reg_masks ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  ui__warning (char*,char*,char*) ; 

__attribute__((used)) static int
__parse_regs(const struct option *opt, const char *str, int unset, bool intr)
{
	uint64_t *mode = (uint64_t *)opt->value;
	const struct sample_reg *r;
	char *s, *os = NULL, *p;
	int ret = -1;
	uint64_t mask;

	if (unset)
		return 0;

	/*
	 * cannot set it twice
	 */
	if (*mode)
		return -1;

	if (intr)
		mask = arch__intr_reg_mask();
	else
		mask = arch__user_reg_mask();

	/* str may be NULL in case no arg is passed to -I */
	if (str) {
		/* because str is read-only */
		s = os = strdup(str);
		if (!s)
			return -1;

		for (;;) {
			p = strchr(s, ',');
			if (p)
				*p = '\0';

			if (!strcmp(s, "?")) {
				fprintf(stderr, "available registers: ");
				for (r = sample_reg_masks; r->name; r++) {
					if (r->mask & mask)
						fprintf(stderr, "%s ", r->name);
				}
				fputc('\n', stderr);
				/* just printing available regs */
				return -1;
			}
			for (r = sample_reg_masks; r->name; r++) {
				if ((r->mask & mask) && !strcasecmp(s, r->name))
					break;
			}
			if (!r->name) {
				ui__warning("Unknown register \"%s\", check man page or run \"perf record %s?\"\n",
					    s, intr ? "-I" : "--user-regs=");
				goto error;
			}

			*mode |= r->mask;

			if (!p)
				break;

			s = p + 1;
		}
	}
	ret = 0;

	/* default to all possible regs */
	if (*mode == 0)
		*mode = mask;
error:
	free(os);
	return ret;
}