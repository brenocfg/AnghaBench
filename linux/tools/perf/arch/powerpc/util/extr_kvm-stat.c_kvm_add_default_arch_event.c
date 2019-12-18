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
struct option {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct option const OPT_BOOLEAN (char,char*,int*,int /*<<< orphan*/ *) ; 
 struct option const OPT_END () ; 
 int /*<<< orphan*/  PARSE_OPT_KEEP_UNKNOWN ; 
 char** calloc (int,int) ; 
 int /*<<< orphan*/  free (char const**) ; 
 int /*<<< orphan*/  parse_options (int,char const**,struct option const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pmu_have_event (char*,char*) ; 
 char* strdup (char*) ; 

int kvm_add_default_arch_event(int *argc, const char **argv)
{
	const char **tmp;
	bool event = false;
	int i, j = *argc;

	const struct option event_options[] = {
		OPT_BOOLEAN('e', "event", &event, NULL),
		OPT_END()
	};

	tmp = calloc(j + 1, sizeof(char *));
	if (!tmp)
		return -EINVAL;

	for (i = 0; i < j; i++)
		tmp[i] = argv[i];

	parse_options(j, tmp, event_options, NULL, PARSE_OPT_KEEP_UNKNOWN);
	if (!event) {
		if (pmu_have_event("trace_imc", "trace_cycles")) {
			argv[j++] = strdup("-e");
			argv[j++] = strdup("trace_imc/trace_cycles/");
			*argc += 2;
		} else {
			free(tmp);
			return -EINVAL;
		}
	}

	free(tmp);
	return 0;
}