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
 char* dirname (char*) ; 
 int do_tests (int,char*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fork_wait () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksft_print_header () ; 
 int /*<<< orphan*/  ksft_print_msg (char*) ; 
 int /*<<< orphan*/  ksft_set_plan (int) ; 
 int /*<<< orphan*/  mpid ; 
 scalar_t__ nerrs ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
	char *tmp1, *tmp2, *our_path;

	/* Find our path */
	tmp1 = strdup(argv[0]);
	if (!tmp1)
		ksft_exit_fail_msg("strdup - %s\n", strerror(errno));
	tmp2 = dirname(tmp1);
	our_path = strdup(tmp2);
	if (!our_path)
		ksft_exit_fail_msg("strdup - %s\n", strerror(errno));
	free(tmp1);

	mpid = getpid();

	if (fork_wait()) {
		ksft_print_header();
		ksft_set_plan(12);
		ksft_print_msg("[RUN]\t+++ Tests with uid == 0 +++\n");
		return do_tests(0, our_path);
	}

	ksft_print_msg("==================================================\n");

	if (fork_wait()) {
		ksft_print_header();
		ksft_set_plan(9);
		ksft_print_msg("[RUN]\t+++ Tests with uid != 0 +++\n");
		return do_tests(1, our_path);
	}

	return nerrs ? 1 : 0;
}