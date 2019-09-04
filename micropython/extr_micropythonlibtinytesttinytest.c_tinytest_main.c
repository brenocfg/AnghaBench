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
struct testgroup_t {TYPE_1__* cases; scalar_t__ prefix; } ;
struct TYPE_2__ {int flags; scalar_t__ name; } ;

/* Variables and functions */
 int TT_ENABLED_ ; 
 int /*<<< orphan*/  in_tinytest_main ; 
 int n_bad ; 
 int n_ok ; 
 int n_skipped ; 
 int opt_forked ; 
 int opt_nofork ; 
 int opt_verbosity ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int process_test_option (struct testgroup_t*,char const*) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  testcase_run_one (struct testgroup_t*,TYPE_1__*) ; 
 int /*<<< orphan*/  tinytest_set_flag_ (struct testgroup_t*,char*,int,int) ; 
 int /*<<< orphan*/  usage (struct testgroup_t*,int) ; 
 char* verbosity_flag ; 

int
tinytest_main(int c, const char **v, struct testgroup_t *groups)
{
	int i, j, n=0;

#ifdef _WIN32
	const char *sp = strrchr(v[0], '.');
	const char *extension = "";
	if (!sp || stricmp(sp, ".exe"))
		extension = ".exe"; /* Add an exe so CreateProcess will work */
	snprintf(commandname, sizeof(commandname), "%s%s", v[0], extension);
	commandname[MAX_PATH]='\0';
#endif
	for (i=1; i<c; ++i) {
		if (v[i][0] == '-') {
			if (!strcmp(v[i], "--RUNNING-FORKED")) {
				opt_forked = 1;
			} else if (!strcmp(v[i], "--no-fork")) {
				opt_nofork = 1;
			} else if (!strcmp(v[i], "--quiet")) {
				opt_verbosity = -1;
				verbosity_flag = "--quiet";
			} else if (!strcmp(v[i], "--verbose")) {
				opt_verbosity = 2;
				verbosity_flag = "--verbose";
			} else if (!strcmp(v[i], "--terse")) {
				opt_verbosity = 0;
				verbosity_flag = "--terse";
			} else if (!strcmp(v[i], "--help")) {
				usage(groups, 0);
			} else if (!strcmp(v[i], "--list-tests")) {
				usage(groups, 1);
			} else {
				printf("Unknown option %s.  Try --help\n",v[i]);
				return -1;
			}
		} else {
			int r = process_test_option(groups, v[i]);
			if (r<0)
				return -1;
			n += r;
		}
	}
	if (!n)
		tinytest_set_flag_(groups, "..", 1, TT_ENABLED_);

#ifdef _IONBF
	setvbuf(stdout, NULL, _IONBF, 0);
#endif

	++in_tinytest_main;
	for (i=0; groups[i].prefix; ++i)
		for (j=0; groups[i].cases[j].name; ++j)
			if (groups[i].cases[j].flags & TT_ENABLED_)
				testcase_run_one(&groups[i],
						 &groups[i].cases[j]);

	--in_tinytest_main;

	if (opt_verbosity==0)
		puts("");

	if (n_bad)
		printf("%d/%d TESTS FAILED. (%d skipped)\n", n_bad,
		       n_bad+n_ok,n_skipped);
	else if (opt_verbosity >= 1)
		printf("%d tests ok.  (%d skipped)\n", n_ok, n_skipped);

	return (n_bad == 0) ? 0 : 1;
}