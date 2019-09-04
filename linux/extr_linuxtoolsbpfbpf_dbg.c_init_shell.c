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
typedef  int /*<<< orphan*/  file ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  emacs_meta_keymap ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  intr_shell ; 
 int /*<<< orphan*/  read_history (char*) ; 
 int /*<<< orphan*/  rl_attempted_completion_function ; 
 int /*<<< orphan*/  rl_bind_key (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rl_bind_key_in_map (char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rl_catch_signals ; 
 int rl_catch_sigwinch ; 
 int /*<<< orphan*/  rl_complete ; 
 int /*<<< orphan*/ * rl_instream ; 
 int /*<<< orphan*/ * rl_outstream ; 
 int /*<<< orphan*/  rl_prep_terminal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rl_read_init_file (char*) ; 
 char* rl_readline_name ; 
 int /*<<< orphan*/  rl_set_signals () ; 
 char* rl_terminal_name ; 
 int /*<<< orphan*/  shell_completion ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static void init_shell(FILE *fin, FILE *fout)
{
	char file[128];

	snprintf(file, sizeof(file), "%s/.bpf_dbg_history", getenv("HOME"));
	read_history(file);

	rl_instream = fin;
	rl_outstream = fout;

	rl_readline_name = "bpf_dbg";
	rl_terminal_name = getenv("TERM");

	rl_catch_signals = 0;
	rl_catch_sigwinch = 1;

	rl_attempted_completion_function = shell_completion;

	rl_bind_key('\t', rl_complete);

	rl_bind_key_in_map('\t', rl_complete, emacs_meta_keymap);
	rl_bind_key_in_map('\033', rl_complete, emacs_meta_keymap);

	snprintf(file, sizeof(file), "%s/.bpf_dbg_init", getenv("HOME"));
	rl_read_init_file(file);

	rl_prep_terminal(0);
	rl_set_signals();

	signal(SIGINT, intr_shell);
}