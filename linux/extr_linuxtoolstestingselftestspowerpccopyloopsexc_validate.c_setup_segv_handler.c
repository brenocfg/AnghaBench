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
struct sigaction {int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_sigaction; } ;
typedef  int /*<<< orphan*/  action ;

/* Variables and functions */
 int /*<<< orphan*/  SA_SIGINFO ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  segv_handler ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void setup_segv_handler(void)
{
	struct sigaction action;

	memset(&action, 0, sizeof(action));
	action.sa_sigaction = segv_handler;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGSEGV, &action, NULL);
}