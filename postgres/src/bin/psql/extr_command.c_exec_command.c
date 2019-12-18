#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ backslashResult ;
struct TYPE_2__ {scalar_t__ cur_cmd_interactive; } ;
typedef  int /*<<< orphan*/  PsqlScanState ;
typedef  int /*<<< orphan*/  PQExpBuffer ;
typedef  int /*<<< orphan*/  ConditionalStack ;

/* Variables and functions */
 scalar_t__ PSQL_CMD_SEND ; 
 scalar_t__ PSQL_CMD_UNKNOWN ; 
 int conditional_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_previous_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ exec_command_C (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_T (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_a (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_cd (int /*<<< orphan*/ ,int,char const*) ; 
 scalar_t__ exec_command_connect (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_conninfo (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_copy (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_copyright (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_crosstabview (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_d (int /*<<< orphan*/ ,int,char const*) ; 
 scalar_t__ exec_command_echo (int /*<<< orphan*/ ,int,char const*) ; 
 scalar_t__ exec_command_edit (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ exec_command_ef_ev (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_elif (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ exec_command_else (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ exec_command_encoding (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_endif (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ exec_command_errverbose (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_f (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_g (int /*<<< orphan*/ ,int,char const*) ; 
 scalar_t__ exec_command_gdesc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_gexec (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_gset (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_help (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_html (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_if (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ exec_command_include (int /*<<< orphan*/ ,int,char const*) ; 
 scalar_t__ exec_command_list (int /*<<< orphan*/ ,int,char const*) ; 
 scalar_t__ exec_command_lo (int /*<<< orphan*/ ,int,char const*) ; 
 scalar_t__ exec_command_out (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_password (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_print (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ exec_command_prompt (int /*<<< orphan*/ ,int,char const*) ; 
 scalar_t__ exec_command_pset (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_quit (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_reset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ exec_command_s (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_set (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_setenv (int /*<<< orphan*/ ,int,char const*) ; 
 scalar_t__ exec_command_sf_sv (int /*<<< orphan*/ ,int,char const*,int) ; 
 scalar_t__ exec_command_shell_escape (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_slash_command_help (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_t (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_timing (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_unset (int /*<<< orphan*/ ,int,char const*) ; 
 scalar_t__ exec_command_watch (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ exec_command_write (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ exec_command_x (int /*<<< orphan*/ ,int) ; 
 scalar_t__ exec_command_z (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_branching_command (char const*) ; 
 int /*<<< orphan*/  pg_log_warning (char*,char const*) ; 
 scalar_t__ pg_strcasecmp (char const*,char*) ; 
 TYPE_1__ pset ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static backslashResult
exec_command(const char *cmd,
			 PsqlScanState scan_state,
			 ConditionalStack cstack,
			 PQExpBuffer query_buf,
			 PQExpBuffer previous_buf)
{
	backslashResult status;
	bool		active_branch = conditional_active(cstack);

	/*
	 * In interactive mode, warn when we're ignoring a command within a false
	 * \if-branch.  But we continue on, so as to parse and discard the right
	 * amount of parameter text.  Each individual backslash command subroutine
	 * is responsible for doing nothing after discarding appropriate
	 * arguments, if !active_branch.
	 */
	if (pset.cur_cmd_interactive && !active_branch &&
		!is_branching_command(cmd))
	{
		pg_log_warning("\\%s command ignored; use \\endif or Ctrl-C to exit current \\if block",
					   cmd);
	}

	if (strcmp(cmd, "a") == 0)
		status = exec_command_a(scan_state, active_branch);
	else if (strcmp(cmd, "C") == 0)
		status = exec_command_C(scan_state, active_branch);
	else if (strcmp(cmd, "c") == 0 || strcmp(cmd, "connect") == 0)
		status = exec_command_connect(scan_state, active_branch);
	else if (strcmp(cmd, "cd") == 0)
		status = exec_command_cd(scan_state, active_branch, cmd);
	else if (strcmp(cmd, "conninfo") == 0)
		status = exec_command_conninfo(scan_state, active_branch);
	else if (pg_strcasecmp(cmd, "copy") == 0)
		status = exec_command_copy(scan_state, active_branch);
	else if (strcmp(cmd, "copyright") == 0)
		status = exec_command_copyright(scan_state, active_branch);
	else if (strcmp(cmd, "crosstabview") == 0)
		status = exec_command_crosstabview(scan_state, active_branch);
	else if (cmd[0] == 'd')
		status = exec_command_d(scan_state, active_branch, cmd);
	else if (strcmp(cmd, "e") == 0 || strcmp(cmd, "edit") == 0)
		status = exec_command_edit(scan_state, active_branch,
								   query_buf, previous_buf);
	else if (strcmp(cmd, "ef") == 0)
		status = exec_command_ef_ev(scan_state, active_branch, query_buf, true);
	else if (strcmp(cmd, "ev") == 0)
		status = exec_command_ef_ev(scan_state, active_branch, query_buf, false);
	else if (strcmp(cmd, "echo") == 0 || strcmp(cmd, "qecho") == 0 ||
			 strcmp(cmd, "warn") == 0)
		status = exec_command_echo(scan_state, active_branch, cmd);
	else if (strcmp(cmd, "elif") == 0)
		status = exec_command_elif(scan_state, cstack, query_buf);
	else if (strcmp(cmd, "else") == 0)
		status = exec_command_else(scan_state, cstack, query_buf);
	else if (strcmp(cmd, "endif") == 0)
		status = exec_command_endif(scan_state, cstack, query_buf);
	else if (strcmp(cmd, "encoding") == 0)
		status = exec_command_encoding(scan_state, active_branch);
	else if (strcmp(cmd, "errverbose") == 0)
		status = exec_command_errverbose(scan_state, active_branch);
	else if (strcmp(cmd, "f") == 0)
		status = exec_command_f(scan_state, active_branch);
	else if (strcmp(cmd, "g") == 0 || strcmp(cmd, "gx") == 0)
		status = exec_command_g(scan_state, active_branch, cmd);
	else if (strcmp(cmd, "gdesc") == 0)
		status = exec_command_gdesc(scan_state, active_branch);
	else if (strcmp(cmd, "gexec") == 0)
		status = exec_command_gexec(scan_state, active_branch);
	else if (strcmp(cmd, "gset") == 0)
		status = exec_command_gset(scan_state, active_branch);
	else if (strcmp(cmd, "h") == 0 || strcmp(cmd, "help") == 0)
		status = exec_command_help(scan_state, active_branch);
	else if (strcmp(cmd, "H") == 0 || strcmp(cmd, "html") == 0)
		status = exec_command_html(scan_state, active_branch);
	else if (strcmp(cmd, "i") == 0 || strcmp(cmd, "include") == 0 ||
			 strcmp(cmd, "ir") == 0 || strcmp(cmd, "include_relative") == 0)
		status = exec_command_include(scan_state, active_branch, cmd);
	else if (strcmp(cmd, "if") == 0)
		status = exec_command_if(scan_state, cstack, query_buf);
	else if (strcmp(cmd, "l") == 0 || strcmp(cmd, "list") == 0 ||
			 strcmp(cmd, "l+") == 0 || strcmp(cmd, "list+") == 0)
		status = exec_command_list(scan_state, active_branch, cmd);
	else if (strncmp(cmd, "lo_", 3) == 0)
		status = exec_command_lo(scan_state, active_branch, cmd);
	else if (strcmp(cmd, "o") == 0 || strcmp(cmd, "out") == 0)
		status = exec_command_out(scan_state, active_branch);
	else if (strcmp(cmd, "p") == 0 || strcmp(cmd, "print") == 0)
		status = exec_command_print(scan_state, active_branch,
									query_buf, previous_buf);
	else if (strcmp(cmd, "password") == 0)
		status = exec_command_password(scan_state, active_branch);
	else if (strcmp(cmd, "prompt") == 0)
		status = exec_command_prompt(scan_state, active_branch, cmd);
	else if (strcmp(cmd, "pset") == 0)
		status = exec_command_pset(scan_state, active_branch);
	else if (strcmp(cmd, "q") == 0 || strcmp(cmd, "quit") == 0)
		status = exec_command_quit(scan_state, active_branch);
	else if (strcmp(cmd, "r") == 0 || strcmp(cmd, "reset") == 0)
		status = exec_command_reset(scan_state, active_branch, query_buf);
	else if (strcmp(cmd, "s") == 0)
		status = exec_command_s(scan_state, active_branch);
	else if (strcmp(cmd, "set") == 0)
		status = exec_command_set(scan_state, active_branch);
	else if (strcmp(cmd, "setenv") == 0)
		status = exec_command_setenv(scan_state, active_branch, cmd);
	else if (strcmp(cmd, "sf") == 0 || strcmp(cmd, "sf+") == 0)
		status = exec_command_sf_sv(scan_state, active_branch, cmd, true);
	else if (strcmp(cmd, "sv") == 0 || strcmp(cmd, "sv+") == 0)
		status = exec_command_sf_sv(scan_state, active_branch, cmd, false);
	else if (strcmp(cmd, "t") == 0)
		status = exec_command_t(scan_state, active_branch);
	else if (strcmp(cmd, "T") == 0)
		status = exec_command_T(scan_state, active_branch);
	else if (strcmp(cmd, "timing") == 0)
		status = exec_command_timing(scan_state, active_branch);
	else if (strcmp(cmd, "unset") == 0)
		status = exec_command_unset(scan_state, active_branch, cmd);
	else if (strcmp(cmd, "w") == 0 || strcmp(cmd, "write") == 0)
		status = exec_command_write(scan_state, active_branch, cmd,
									query_buf, previous_buf);
	else if (strcmp(cmd, "watch") == 0)
		status = exec_command_watch(scan_state, active_branch,
									query_buf, previous_buf);
	else if (strcmp(cmd, "x") == 0)
		status = exec_command_x(scan_state, active_branch);
	else if (strcmp(cmd, "z") == 0)
		status = exec_command_z(scan_state, active_branch);
	else if (strcmp(cmd, "!") == 0)
		status = exec_command_shell_escape(scan_state, active_branch);
	else if (strcmp(cmd, "?") == 0)
		status = exec_command_slash_command_help(scan_state, active_branch);
	else
		status = PSQL_CMD_UNKNOWN;

	/*
	 * All the commands that return PSQL_CMD_SEND want to execute previous_buf
	 * if query_buf is empty.  For convenience we implement that here, not in
	 * the individual command subroutines.
	 */
	if (status == PSQL_CMD_SEND)
		copy_previous_query(query_buf, previous_buf);

	return status;
}