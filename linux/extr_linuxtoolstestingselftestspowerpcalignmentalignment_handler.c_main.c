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
struct sigaction {int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_sigaction; } ;

/* Variables and functions */
 int /*<<< orphan*/  SA_SIGINFO ; 
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  bufsize ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  getpagesize () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sighandler ; 
 int /*<<< orphan*/  test_alignment_handler_fp ; 
 int /*<<< orphan*/  test_alignment_handler_fp_205 ; 
 int /*<<< orphan*/  test_alignment_handler_fp_206 ; 
 int /*<<< orphan*/  test_alignment_handler_integer ; 
 int /*<<< orphan*/  test_alignment_handler_integer_206 ; 
 int /*<<< orphan*/  test_alignment_handler_vmx ; 
 int /*<<< orphan*/  test_alignment_handler_vsx_206 ; 
 int /*<<< orphan*/  test_alignment_handler_vsx_207 ; 
 int /*<<< orphan*/  test_alignment_handler_vsx_300 ; 
 int test_harness (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char *argv[])
{

	struct sigaction sa;
	int rc = 0;
	int option = 0;

	while ((option = getopt(argc, argv, "d")) != -1) {
		switch (option) {
		case 'd':
			debug++;
			break;
		default:
			usage(argv[0]);
			exit(1);
		}
	}

	bufsize = getpagesize();

	sa.sa_sigaction = sighandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGSEGV, &sa, NULL) == -1
	    || sigaction(SIGBUS, &sa, NULL) == -1
	    || sigaction(SIGILL, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}

	rc |= test_harness(test_alignment_handler_vsx_206,
			   "test_alignment_handler_vsx_206");
	rc |= test_harness(test_alignment_handler_vsx_207,
			   "test_alignment_handler_vsx_207");
	rc |= test_harness(test_alignment_handler_vsx_300,
			   "test_alignment_handler_vsx_300");
	rc |= test_harness(test_alignment_handler_integer,
			   "test_alignment_handler_integer");
	rc |= test_harness(test_alignment_handler_integer_206,
			   "test_alignment_handler_integer_206");
	rc |= test_harness(test_alignment_handler_vmx,
			   "test_alignment_handler_vmx");
	rc |= test_harness(test_alignment_handler_fp,
			   "test_alignment_handler_fp");
	rc |= test_harness(test_alignment_handler_fp_205,
			   "test_alignment_handler_fp_205");
	rc |= test_harness(test_alignment_handler_fp_206,
			   "test_alignment_handler_fp_206");
	return rc;
}