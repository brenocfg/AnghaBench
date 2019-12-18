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
 int /*<<< orphan*/  SLang_init_tty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLang_reset_tty () ; 
 int /*<<< orphan*/  SLsmg_refresh () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 int /*<<< orphan*/  pr_warning (char*,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ system (char*) ; 

void run_script(char *cmd)
{
	pr_debug("Running %s\n", cmd);
	SLang_reset_tty();
	if (system(cmd) < 0)
		pr_warning("Cannot run %s\n", cmd);
	/*
	 * SLang doesn't seem to reset the whole terminal, so be more
	 * forceful to get back to the original state.
	 */
	printf("\033[c\033[H\033[J");
	fflush(stdout);
	SLang_init_tty(0, 0, 0);
	SLsmg_refresh();
}