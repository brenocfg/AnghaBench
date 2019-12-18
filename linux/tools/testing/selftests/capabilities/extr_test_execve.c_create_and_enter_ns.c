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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAPNG_ADD ; 
 int /*<<< orphan*/  CAPNG_EFFECTIVE ; 
 int /*<<< orphan*/  CAPNG_PERMITTED ; 
 int /*<<< orphan*/  CAPNG_SELECT_CAPS ; 
 int CAP_LAST_CAP ; 
 int CLONE_NEWNS ; 
 int CLONE_NEWUSER ; 
 int MS_PRIVATE ; 
 int MS_REC ; 
 int /*<<< orphan*/  PR_SET_KEEPCAPS ; 
 scalar_t__ capng_apply (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capng_get_caps_process () ; 
 scalar_t__ capng_have_capability (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  capng_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  getgid () ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksft_exit_skip (char*) ; 
 int /*<<< orphan*/  ksft_print_msg (char*) ; 
 int /*<<< orphan*/  maybe_write_file (char*,char*) ; 
 scalar_t__ mount (char*,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ prctl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ setresuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ unshare (int) ; 
 int /*<<< orphan*/  write_file (char*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static bool create_and_enter_ns(uid_t inner_uid)
{
	uid_t outer_uid;
	gid_t outer_gid;
	int i;
	bool have_outer_privilege;

	outer_uid = getuid();
	outer_gid = getgid();

	/*
	 * TODO: If we're already root, we could skip creating the userns.
	 */

	if (unshare(CLONE_NEWNS) == 0) {
		ksft_print_msg("[NOTE]\tUsing global UIDs for tests\n");
		if (prctl(PR_SET_KEEPCAPS, 1, 0, 0, 0) != 0)
			ksft_exit_fail_msg("PR_SET_KEEPCAPS - %s\n",
						strerror(errno));
		if (setresuid(inner_uid, inner_uid, -1) != 0)
			ksft_exit_fail_msg("setresuid - %s\n", strerror(errno));

		// Re-enable effective caps
		capng_get_caps_process();
		for (i = 0; i < CAP_LAST_CAP; i++)
			if (capng_have_capability(CAPNG_PERMITTED, i))
				capng_update(CAPNG_ADD, CAPNG_EFFECTIVE, i);
		if (capng_apply(CAPNG_SELECT_CAPS) != 0)
			ksft_exit_fail_msg(
					"capng_apply - %s\n", strerror(errno));

		have_outer_privilege = true;
	} else if (unshare(CLONE_NEWUSER | CLONE_NEWNS) == 0) {
		ksft_print_msg("[NOTE]\tUsing a user namespace for tests\n");
		maybe_write_file("/proc/self/setgroups", "deny");
		write_file("/proc/self/uid_map", "%d %d 1", inner_uid, outer_uid);
		write_file("/proc/self/gid_map", "0 %d 1", outer_gid);

		have_outer_privilege = false;
	} else {
		ksft_exit_skip("must be root or be able to create a userns\n");
	}

	if (mount("none", "/", NULL, MS_REC | MS_PRIVATE, NULL) != 0)
		ksft_exit_fail_msg("remount everything private - %s\n",
					strerror(errno));

	return have_outer_privilege;
}