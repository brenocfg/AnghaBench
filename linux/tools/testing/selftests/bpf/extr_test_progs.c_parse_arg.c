#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* name; } ;
struct test_env {int verifier_stats; int very_verbose; int verbose; TYPE_1__ test_selector; TYPE_1__ subtest_selector; } ;
struct argp_state {struct test_env* input; } ;
typedef  int /*<<< orphan*/  error_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARGP_ERR_UNKNOWN ; 
#define  ARGP_KEY_ARG 133 
#define  ARGP_KEY_END 132 
#define  ARG_TEST_NAME 131 
#define  ARG_TEST_NUM 130 
#define  ARG_VERBOSE 129 
#define  ARG_VERIFIER_STATS 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  argp_usage (struct argp_state*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  parse_num_list (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 void* strdup (char*) ; 

__attribute__((used)) static error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	struct test_env *env = state->input;

	switch (key) {
	case ARG_TEST_NUM: {
		char *subtest_str = strchr(arg, '/');

		if (subtest_str) {
			*subtest_str = '\0';
			if (parse_num_list(subtest_str + 1,
					   &env->subtest_selector)) {
				fprintf(stderr,
					"Failed to parse subtest numbers.\n");
				return -EINVAL;
			}
		}
		if (parse_num_list(arg, &env->test_selector)) {
			fprintf(stderr, "Failed to parse test numbers.\n");
			return -EINVAL;
		}
		break;
	}
	case ARG_TEST_NAME: {
		char *subtest_str = strchr(arg, '/');

		if (subtest_str) {
			*subtest_str = '\0';
			env->subtest_selector.name = strdup(subtest_str + 1);
			if (!env->subtest_selector.name)
				return -ENOMEM;
		}
		env->test_selector.name = strdup(arg);
		if (!env->test_selector.name)
			return -ENOMEM;
		break;
	}
	case ARG_VERIFIER_STATS:
		env->verifier_stats = true;
		break;
	case ARG_VERBOSE:
		if (arg) {
			if (strcmp(arg, "v") == 0) {
				env->very_verbose = true;
			} else {
				fprintf(stderr,
					"Unrecognized verbosity setting ('%s'), only -v and -vv are supported\n",
					arg);
				return -EINVAL;
			}
		}
		env->verbose = true;
		break;
	case ARGP_KEY_ARG:
		argp_usage(state);
		break;
	case ARGP_KEY_END:
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}