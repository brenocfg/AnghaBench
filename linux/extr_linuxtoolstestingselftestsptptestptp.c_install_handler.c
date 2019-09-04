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
struct sigaction {void (* sa_handler ) (int) ;int /*<<< orphan*/  sa_mask; scalar_t__ sa_flags; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int /*<<< orphan*/  sigaction (int,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int install_handler(int signum, void (*handler)(int))
{
	struct sigaction action;
	sigset_t mask;

	/* Unblock the signal. */
	sigemptyset(&mask);
	sigaddset(&mask, signum);
	sigprocmask(SIG_UNBLOCK, &mask, NULL);

	/* Install the signal handler. */
	action.sa_handler = handler;
	action.sa_flags = 0;
	sigemptyset(&action.sa_mask);
	sigaction(signum, &action, NULL);

	return 0;
}