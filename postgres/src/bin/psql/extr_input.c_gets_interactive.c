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
typedef  int /*<<< orphan*/ * PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ ) ; 
 char* gets_fromFile (int /*<<< orphan*/ ) ; 
 char* readline (char*) ; 
 int /*<<< orphan*/  rl_reset_screen_size () ; 
 int sigint_interrupt_enabled ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/ * tab_completion_query_buf ; 
 scalar_t__ useReadline ; 

char *
gets_interactive(const char *prompt, PQExpBuffer query_buf)
{
#ifdef USE_READLINE
	if (useReadline)
	{
		char	   *result;

		/*
		 * Some versions of readline don't notice SIGWINCH signals that arrive
		 * when not actively reading input.  The simplest fix is to always
		 * re-read the terminal size.  This leaves a window for SIGWINCH to be
		 * missed between here and where readline() enables libreadline's
		 * signal handler, but that's probably short enough to be ignored.
		 */
#ifdef HAVE_RL_RESET_SCREEN_SIZE
		rl_reset_screen_size();
#endif

		/* Make current query_buf available to tab completion callback */
		tab_completion_query_buf = query_buf;

		/* Enable SIGINT to longjmp to sigint_interrupt_jmp */
		sigint_interrupt_enabled = true;

		/* On some platforms, readline is declared as readline(char *) */
		result = readline((char *) prompt);

		/* Disable SIGINT again */
		sigint_interrupt_enabled = false;

		/* Pure neatnik-ism */
		tab_completion_query_buf = NULL;

		return result;
	}
#endif

	fputs(prompt, stdout);
	fflush(stdout);
	return gets_fromFile(stdin);
}