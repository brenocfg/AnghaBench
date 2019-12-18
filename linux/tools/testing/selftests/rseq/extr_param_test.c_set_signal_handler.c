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
struct sigaction {scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf_verbose (char*) ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_signal_interrupt_handler ; 

__attribute__((used)) static int set_signal_handler(void)
{
	int ret = 0;
	struct sigaction sa;
	sigset_t sigset;

	ret = sigemptyset(&sigset);
	if (ret < 0) {
		perror("sigemptyset");
		return ret;
	}

	sa.sa_handler = test_signal_interrupt_handler;
	sa.sa_mask = sigset;
	sa.sa_flags = 0;
	ret = sigaction(SIGUSR1, &sa, NULL);
	if (ret < 0) {
		perror("sigaction");
		return ret;
	}

	printf_verbose("Signal handler set for SIGUSR1\n");

	return ret;
}