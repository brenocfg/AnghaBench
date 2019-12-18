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
struct stat {scalar_t__ st_uid; scalar_t__ st_size; } ;
struct perf_config_set {int dummy; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  R_OK ; 
 int /*<<< orphan*/  access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  collect_config ; 
 char* config_exclusive_filename ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  mkpath (char*,char const*) ; 
 int perf_config_from_file (int /*<<< orphan*/ ,char*,struct perf_config_set*) ; 
 int /*<<< orphan*/  perf_config_global () ; 
 scalar_t__ perf_config_system () ; 
 char* perf_etc_perfconfig () ; 
 int /*<<< orphan*/  pr_warning (char*,char const*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perf_config_set__init(struct perf_config_set *set)
{
	int ret = -1;
	const char *home = NULL;
	char *user_config;
	struct stat st;

	/* Setting $PERF_CONFIG makes perf read _only_ the given config file. */
	if (config_exclusive_filename)
		return perf_config_from_file(collect_config, config_exclusive_filename, set);
	if (perf_config_system() && !access(perf_etc_perfconfig(), R_OK)) {
		if (perf_config_from_file(collect_config, perf_etc_perfconfig(), set) < 0)
			goto out;
	}

	home = getenv("HOME");

	/*
	 * Skip reading user config if:
	 *   - there is no place to read it from (HOME)
	 *   - we are asked not to (PERF_CONFIG_NOGLOBAL=1)
	 */
	if (!home || !*home || !perf_config_global())
		return 0;

	user_config = strdup(mkpath("%s/.perfconfig", home));
	if (user_config == NULL) {
		pr_warning("Not enough memory to process %s/.perfconfig, ignoring it.", home);
		goto out;
	}

	if (stat(user_config, &st) < 0) {
		if (errno == ENOENT)
			ret = 0;
		goto out_free;
	}

	ret = 0;

	if (st.st_uid && (st.st_uid != geteuid())) {
		pr_warning("File %s not owned by current user or root, ignoring it.", user_config);
		goto out_free;
	}

	if (st.st_size)
		ret = perf_config_from_file(collect_config, user_config, set);

out_free:
	free(user_config);
out:
	return ret;
}