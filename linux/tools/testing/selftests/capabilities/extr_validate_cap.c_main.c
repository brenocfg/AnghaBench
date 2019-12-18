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
 int /*<<< orphan*/  AT_SECURE ; 
 int /*<<< orphan*/  CAPNG_EFFECTIVE ; 
 int /*<<< orphan*/  CAPNG_INHERITABLE ; 
 int /*<<< orphan*/  CAPNG_PERMITTED ; 
 int /*<<< orphan*/  CAP_NET_BIND_SERVICE ; 
 int /*<<< orphan*/  PR_CAP_AMBIENT ; 
 int /*<<< orphan*/  PR_CAP_AMBIENT_IS_SET ; 
 scalar_t__ bool_arg (char**,int) ; 
 int /*<<< orphan*/  capng_get_caps_process () ; 
 scalar_t__ capng_have_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getauxval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*) ; 
 int /*<<< orphan*/  ksft_print_msg (char*,char const*) ; 
 scalar_t__ prctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
	const char *atsec = "";

	/*
	 * Be careful just in case a setgid or setcapped copy of this
	 * helper gets out.
	 */

	if (argc != 5)
		ksft_exit_fail_msg("wrong argc\n");

#ifdef HAVE_GETAUXVAL
	if (getauxval(AT_SECURE))
		atsec = " (AT_SECURE is set)";
	else
		atsec = " (AT_SECURE is not set)";
#endif

	capng_get_caps_process();

	if (capng_have_capability(CAPNG_EFFECTIVE, CAP_NET_BIND_SERVICE) != bool_arg(argv, 1)) {
		ksft_print_msg("Wrong effective state%s\n", atsec);
		return 1;
	}

	if (capng_have_capability(CAPNG_PERMITTED, CAP_NET_BIND_SERVICE) != bool_arg(argv, 2)) {
		ksft_print_msg("Wrong permitted state%s\n", atsec);
		return 1;
	}

	if (capng_have_capability(CAPNG_INHERITABLE, CAP_NET_BIND_SERVICE) != bool_arg(argv, 3)) {
		ksft_print_msg("Wrong inheritable state%s\n", atsec);
		return 1;
	}

	if (prctl(PR_CAP_AMBIENT, PR_CAP_AMBIENT_IS_SET, CAP_NET_BIND_SERVICE, 0, 0, 0) != bool_arg(argv, 4)) {
		ksft_print_msg("Wrong ambient state%s\n", atsec);
		return 1;
	}

	ksft_print_msg("%s: Capabilities after execve were correct\n",
			"validate_cap:");
	return 0;
}