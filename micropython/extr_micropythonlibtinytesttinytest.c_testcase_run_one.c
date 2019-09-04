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
struct testgroup_t {char* prefix; } ;
struct testcase_t {int flags; char* name; } ;
typedef  enum outcome { ____Placeholder_outcome } outcome ;

/* Variables and functions */
 int MAGIC_EXITCODE ; 
 int OK ; 
 int SKIP ; 
 int TT_FORK ; 
 int TT_OFF_BY_DEFAULT ; 
 int TT_SKIP ; 
 char* cur_test_name ; 
 char* cur_test_prefix ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  n_bad ; 
 int /*<<< orphan*/  n_ok ; 
 int /*<<< orphan*/  n_skipped ; 
 scalar_t__ opt_forked ; 
 scalar_t__ opt_nofork ; 
 int opt_verbosity ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int testcase_run_bare_ (struct testcase_t const*) ; 
 int testcase_run_forked_ (struct testgroup_t const*,struct testcase_t const*) ; 

int
testcase_run_one(const struct testgroup_t *group,
		 const struct testcase_t *testcase)
{
	enum outcome outcome;

	if (testcase->flags & (TT_SKIP|TT_OFF_BY_DEFAULT)) {
		if (opt_verbosity>0)
			printf("%s%s: %s\n",
			   group->prefix, testcase->name,
			   (testcase->flags & TT_SKIP) ? "SKIPPED" : "DISABLED");
		++n_skipped;
		return SKIP;
	}

	printf("# starting %s%s\n", group->prefix, testcase->name);
	if (opt_verbosity>0 && !opt_forked) {
		//printf("%s%s: ", group->prefix, testcase->name);
	} else {
		if (opt_verbosity==0) printf(".");
		cur_test_prefix = group->prefix;
		cur_test_name = testcase->name;
	}

#ifndef NO_FORKING
	if ((testcase->flags & TT_FORK) && !(opt_forked||opt_nofork)) {
		outcome = testcase_run_forked_(group, testcase);
	} else {
#else
	{
#endif
		outcome = testcase_run_bare_(testcase);
	}

	printf("%s%s: ", group->prefix, testcase->name);
	if (outcome == OK) {
		++n_ok;
		if (opt_verbosity>0 && !opt_forked)
			puts(opt_verbosity==1?"OK":"");
	} else if (outcome == SKIP) {
		++n_skipped;
		if (opt_verbosity>0 && !opt_forked)
			puts("SKIPPED");
	} else {
		++n_bad;
		if (!opt_forked)
			//printf("\n  [%s FAILED]\n", testcase->name);
			puts("FAILED");
	}

	if (opt_forked) {
		exit(outcome==OK ? 0 : (outcome==SKIP?MAGIC_EXITCODE : 1));
		return 1; /* unreachable */
	} else {
		return (int)outcome;
	}
}