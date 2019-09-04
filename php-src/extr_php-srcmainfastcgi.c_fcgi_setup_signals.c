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
struct sigaction {scalar_t__ sa_handler; scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 scalar_t__ SIG_DFL ; 
 scalar_t__ fcgi_signal_handler ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fcgi_setup_signals(void)
{
	struct sigaction new_sa, old_sa;

	sigemptyset(&new_sa.sa_mask);
	new_sa.sa_flags = 0;
	new_sa.sa_handler = fcgi_signal_handler;
	sigaction(SIGUSR1, &new_sa, NULL);
	sigaction(SIGTERM, &new_sa, NULL);
	sigaction(SIGPIPE, NULL, &old_sa);
	if (old_sa.sa_handler == SIG_DFL) {
		sigaction(SIGPIPE, &new_sa, NULL);
	}
}