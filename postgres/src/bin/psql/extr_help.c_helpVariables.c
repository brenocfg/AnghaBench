#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  topt; } ;
struct TYPE_4__ {TYPE_1__ popt; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ClosePager (int /*<<< orphan*/ *) ; 
 char* DEFAULT_FIELD_SEP ; 
 int /*<<< orphan*/ * PageOutput (int,int /*<<< orphan*/ *) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_2__ pset ; 

void
helpVariables(unsigned short int pager)
{
	FILE	   *output;

	/*
	 * Keep this line count in sync with the number of lines printed below!
	 * Use "psql --help=variables | wc" to count correctly; but notice that
	 * Windows builds currently print one more line than non-Windows builds.
	 * Using the larger number is fine.
	 */
	output = PageOutput(158, pager ? &(pset.popt.topt) : NULL);

	fprintf(output, _("List of specially treated variables\n\n"));

	fprintf(output, _("psql variables:\n"));
	fprintf(output, _("Usage:\n"));
	fprintf(output, _("  psql --set=NAME=VALUE\n  or \\set NAME VALUE inside psql\n\n"));

	fprintf(output, _("  AUTOCOMMIT\n"
					  "    if set, successful SQL commands are automatically committed\n"));
	fprintf(output, _("  COMP_KEYWORD_CASE\n"
					  "    determines the case used to complete SQL key words\n"
					  "    [lower, upper, preserve-lower, preserve-upper]\n"));
	fprintf(output, _("  DBNAME\n"
					  "    the currently connected database name\n"));
	fprintf(output, _("  ECHO\n"
					  "    controls what input is written to standard output\n"
					  "    [all, errors, none, queries]\n"));
	fprintf(output, _("  ECHO_HIDDEN\n"
					  "    if set, display internal queries executed by backslash commands;\n"
					  "    if set to \"noexec\", just show them without execution\n"));
	fprintf(output, _("  ENCODING\n"
					  "    current client character set encoding\n"));
	fprintf(output, _("  ERROR\n"
					  "    true if last query failed, else false\n"));
	fprintf(output, _("  FETCH_COUNT\n"
					  "    the number of result rows to fetch and display at a time (0 = unlimited)\n"));
	fprintf(output, _("  HIDE_TABLEAM\n"
					  "    if set, table access methods are not displayed\n"));
	fprintf(output, _("  HISTCONTROL\n"
					  "    controls command history [ignorespace, ignoredups, ignoreboth]\n"));
	fprintf(output, _("  HISTFILE\n"
					  "    file name used to store the command history\n"));
	fprintf(output, _("  HISTSIZE\n"
					  "    maximum number of commands to store in the command history\n"));
	fprintf(output, _("  HOST\n"
					  "    the currently connected database server host\n"));
	fprintf(output, _("  IGNOREEOF\n"
					  "    number of EOFs needed to terminate an interactive session\n"));
	fprintf(output, _("  LASTOID\n"
					  "    value of the last affected OID\n"));
	fprintf(output, _("  LAST_ERROR_MESSAGE\n"
					  "  LAST_ERROR_SQLSTATE\n"
					  "    message and SQLSTATE of last error, or empty string and \"00000\" if none\n"));
	fprintf(output, _("  ON_ERROR_ROLLBACK\n"
					  "    if set, an error doesn't stop a transaction (uses implicit savepoints)\n"));
	fprintf(output, _("  ON_ERROR_STOP\n"
					  "    stop batch execution after error\n"));
	fprintf(output, _("  PORT\n"
					  "    server port of the current connection\n"));
	fprintf(output, _("  PROMPT1\n"
					  "    specifies the standard psql prompt\n"));
	fprintf(output, _("  PROMPT2\n"
					  "    specifies the prompt used when a statement continues from a previous line\n"));
	fprintf(output, _("  PROMPT3\n"
					  "    specifies the prompt used during COPY ... FROM STDIN\n"));
	fprintf(output, _("  QUIET\n"
					  "    run quietly (same as -q option)\n"));
	fprintf(output, _("  ROW_COUNT\n"
					  "    number of rows returned or affected by last query, or 0\n"));
	fprintf(output, _("  SERVER_VERSION_NAME\n"
					  "  SERVER_VERSION_NUM\n"
					  "    server's version (in short string or numeric format)\n"));
	fprintf(output, _("  SHOW_CONTEXT\n"
					  "    controls display of message context fields [never, errors, always]\n"));
	fprintf(output, _("  SINGLELINE\n"
					  "    if set, end of line terminates SQL commands (same as -S option)\n"));
	fprintf(output, _("  SINGLESTEP\n"
					  "    single-step mode (same as -s option)\n"));
	fprintf(output, _("  SQLSTATE\n"
					  "    SQLSTATE of last query, or \"00000\" if no error\n"));
	fprintf(output, _("  USER\n"
					  "    the currently connected database user\n"));
	fprintf(output, _("  VERBOSITY\n"
					  "    controls verbosity of error reports [default, verbose, terse, sqlstate]\n"));
	fprintf(output, _("  VERSION\n"
					  "  VERSION_NAME\n"
					  "  VERSION_NUM\n"
					  "    psql's version (in verbose string, short string, or numeric format)\n"));

	fprintf(output, _("\nDisplay settings:\n"));
	fprintf(output, _("Usage:\n"));
	fprintf(output, _("  psql --pset=NAME[=VALUE]\n  or \\pset NAME [VALUE] inside psql\n\n"));

	fprintf(output, _("  border\n"
					  "    border style (number)\n"));
	fprintf(output, _("  columns\n"
					  "    target width for the wrapped format\n"));
	fprintf(output, _("  expanded (or x)\n"
					  "    expanded output [on, off, auto]\n"));
	fprintf(output, _("  fieldsep\n"
					  "    field separator for unaligned output (default \"%s\")\n"),
			DEFAULT_FIELD_SEP);
	fprintf(output, _("  fieldsep_zero\n"
					  "    set field separator for unaligned output to a zero byte\n"));
	fprintf(output, _("  footer\n"
					  "    enable or disable display of the table footer [on, off]\n"));
	fprintf(output, _("  format\n"
					  "    set output format [unaligned, aligned, wrapped, html, asciidoc, ...]\n"));
	fprintf(output, _("  linestyle\n"
					  "    set the border line drawing style [ascii, old-ascii, unicode]\n"));
	fprintf(output, _("  null\n"
					  "    set the string to be printed in place of a null value\n"));
	fprintf(output, _("  numericlocale\n"
					  "    enable display of a locale-specific character to separate groups of digits\n"));
	fprintf(output, _("  pager\n"
					  "    control when an external pager is used [yes, no, always]\n"));
	fprintf(output, _("  recordsep\n"
					  "    record (line) separator for unaligned output\n"));
	fprintf(output, _("  recordsep_zero\n"
					  "    set record separator for unaligned output to a zero byte\n"));
	fprintf(output, _("  tableattr (or T)\n"
					  "    specify attributes for table tag in html format, or proportional\n"
					  "    column widths for left-aligned data types in latex-longtable format\n"));
	fprintf(output, _("  title\n"
					  "    set the table title for subsequently printed tables\n"));
	fprintf(output, _("  tuples_only\n"
					  "    if set, only actual table data is shown\n"));
	fprintf(output, _("  unicode_border_linestyle\n"
					  "  unicode_column_linestyle\n"
					  "  unicode_header_linestyle\n"
					  "    set the style of Unicode line drawing [single, double]\n"));

	fprintf(output, _("\nEnvironment variables:\n"));
	fprintf(output, _("Usage:\n"));

#ifndef WIN32
	fprintf(output, _("  NAME=VALUE [NAME=VALUE] psql ...\n  or \\setenv NAME [VALUE] inside psql\n\n"));
#else
	fprintf(output, _("  set NAME=VALUE\n  psql ...\n  or \\setenv NAME [VALUE] inside psql\n\n"));
#endif

	fprintf(output, _("  COLUMNS\n"
					  "    number of columns for wrapped format\n"));
	fprintf(output, _("  PGAPPNAME\n"
					  "    same as the application_name connection parameter\n"));
	fprintf(output, _("  PGDATABASE\n"
					  "    same as the dbname connection parameter\n"));
	fprintf(output, _("  PGHOST\n"
					  "    same as the host connection parameter\n"));
	fprintf(output, _("  PGPASSWORD\n"
					  "    connection password (not recommended)\n"));
	fprintf(output, _("  PGPASSFILE\n"
					  "    password file name\n"));
	fprintf(output, _("  PGPORT\n"
					  "    same as the port connection parameter\n"));
	fprintf(output, _("  PGUSER\n"
					  "    same as the user connection parameter\n"));
	fprintf(output, _("  PSQL_EDITOR, EDITOR, VISUAL\n"
					  "    editor used by the \\e, \\ef, and \\ev commands\n"));
	fprintf(output, _("  PSQL_EDITOR_LINENUMBER_ARG\n"
					  "    how to specify a line number when invoking the editor\n"));
	fprintf(output, _("  PSQL_HISTORY\n"
					  "    alternative location for the command history file\n"));
	fprintf(output, _("  PSQL_PAGER, PAGER\n"
					  "    name of external pager program\n"));
	fprintf(output, _("  PSQLRC\n"
					  "    alternative location for the user's .psqlrc file\n"));
	fprintf(output, _("  SHELL\n"
					  "    shell used by the \\! command\n"));
	fprintf(output, _("  TMPDIR\n"
					  "    directory for temporary files\n"));

	ClosePager(output);
}