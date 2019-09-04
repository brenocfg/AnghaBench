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
struct option {scalar_t__ value; } ;
struct mem_mode {int mode; scalar_t__ name; } ;

/* Variables and functions */
 int MEM_OPERATION_LOAD ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct mem_mode* mem_modes ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcasecmp (char*,scalar_t__) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int
parse_mem_ops(const struct option *opt, const char *str, int unset)
{
	int *mode = (int *)opt->value;
	const struct mem_mode *m;
	char *s, *os = NULL, *p;
	int ret = -1;

	if (unset)
		return 0;

	/* str may be NULL in case no arg is passed to -t */
	if (str) {
		/* because str is read-only */
		s = os = strdup(str);
		if (!s)
			return -1;

		/* reset mode */
		*mode = 0;

		for (;;) {
			p = strchr(s, ',');
			if (p)
				*p = '\0';

			for (m = mem_modes; m->name; m++) {
				if (!strcasecmp(s, m->name))
					break;
			}
			if (!m->name) {
				fprintf(stderr, "unknown sampling op %s,"
					    " check man page\n", s);
				goto error;
			}

			*mode |= m->mode;

			if (!p)
				break;

			s = p + 1;
		}
	}
	ret = 0;

	if (*mode == 0)
		*mode = MEM_OPERATION_LOAD;
error:
	free(os);
	return ret;
}