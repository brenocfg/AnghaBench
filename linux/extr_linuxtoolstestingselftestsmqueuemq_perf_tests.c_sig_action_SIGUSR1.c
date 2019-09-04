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
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ main_thread ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_self () ; 
 int /*<<< orphan*/  shutdown (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void sig_action_SIGUSR1(int signum, siginfo_t *info, void *context)
{
	if (pthread_self() != main_thread)
		pthread_exit(0);
	else {
		fprintf(stderr, "Caught signal %d in SIGUSR1 handler, "
				"exiting\n", signum);
		shutdown(0, "", 0);
		fprintf(stderr, "\n\nReturned from shutdown?!?!\n\n");
		exit(0);
	}
}