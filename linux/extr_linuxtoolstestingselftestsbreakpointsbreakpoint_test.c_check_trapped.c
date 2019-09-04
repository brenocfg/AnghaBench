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
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_tests ; 
 scalar_t__ trapped ; 

__attribute__((used)) static void check_trapped(void)
{
	/*
	 * If we haven't trapped, wake up the parent
	 * so that it notices the failure.
	 */
	if (!trapped)
		kill(getpid(), SIGUSR1);
	trapped = 0;

	nr_tests++;
}