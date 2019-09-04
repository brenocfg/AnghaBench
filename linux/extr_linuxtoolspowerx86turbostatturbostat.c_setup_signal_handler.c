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
struct sigaction {int /*<<< orphan*/ * sa_handler; } ;
typedef  int /*<<< orphan*/  sa ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler ; 

void setup_signal_handler(void)
{
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));

	sa.sa_handler = &signal_handler;

	if (sigaction(SIGINT, &sa, NULL) < 0)
		err(1, "sigaction SIGINT");
	if (sigaction(SIGUSR1, &sa, NULL) < 0)
		err(1, "sigaction SIGUSR1");
}