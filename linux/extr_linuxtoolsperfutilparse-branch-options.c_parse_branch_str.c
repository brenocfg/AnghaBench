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
struct branch_mode {int mode; scalar_t__ name; } ;
typedef  int __u64 ;

/* Variables and functions */
 int PERF_SAMPLE_BRANCH_ANY ; 
 int PERF_SAMPLE_BRANCH_HV ; 
 int PERF_SAMPLE_BRANCH_KERNEL ; 
 int PERF_SAMPLE_BRANCH_USER ; 
 struct branch_mode* branch_modes ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pr_warning (char*,char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,scalar_t__) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 

int parse_branch_str(const char *str, __u64 *mode)
{
#define ONLY_PLM \
	(PERF_SAMPLE_BRANCH_USER	|\
	 PERF_SAMPLE_BRANCH_KERNEL	|\
	 PERF_SAMPLE_BRANCH_HV)

	int ret = 0;
	char *p, *s;
	char *os = NULL;
	const struct branch_mode *br;

	if (str == NULL) {
		*mode = PERF_SAMPLE_BRANCH_ANY;
		return 0;
	}

	/* because str is read-only */
	s = os = strdup(str);
	if (!s)
		return -1;

	for (;;) {
		p = strchr(s, ',');
		if (p)
			*p = '\0';

		for (br = branch_modes; br->name; br++) {
			if (!strcasecmp(s, br->name))
				break;
		}
		if (!br->name) {
			ret = -1;
			pr_warning("unknown branch filter %s,"
				    " check man page\n", s);
			goto error;
		}

		*mode |= br->mode;

		if (!p)
			break;

		s = p + 1;
	}

	/* default to any branch */
	if ((*mode & ~ONLY_PLM) == 0) {
		*mode = PERF_SAMPLE_BRANCH_ANY;
	}
error:
	free(os);
	return ret;
}