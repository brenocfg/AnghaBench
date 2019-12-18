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
 char* _ (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
help(const char *progname)
{
	printf(_("%s is the PostgreSQL embedded SQL preprocessor for C programs.\n\n"),
		   progname);
	printf(_("Usage:\n"
			 "  %s [OPTION]... FILE...\n\n"),
		   progname);
	printf(_("Options:\n"));
	printf(_("  -c             automatically generate C code from embedded SQL code;\n"
			 "                 this affects EXEC SQL TYPE\n"));
	printf(_("  -C MODE        set compatibility mode; MODE can be one of\n"
			 "                 \"INFORMIX\", \"INFORMIX_SE\", \"ORACLE\"\n"));
#ifdef YYDEBUG
	printf(_("  -d             generate parser debug output\n"));
#endif
	printf(_("  -D SYMBOL      define SYMBOL\n"));
	printf(_("  -h             parse a header file, this option includes option \"-c\"\n"));
	printf(_("  -i             parse system include files as well\n"));
	printf(_("  -I DIRECTORY   search DIRECTORY for include files\n"));
	printf(_("  -o OUTFILE     write result to OUTFILE\n"));
	printf(_("  -r OPTION      specify run-time behavior; OPTION can be:\n"
			 "                 \"no_indicator\", \"prepare\", \"questionmarks\"\n"));
	printf(_("  --regression   run in regression testing mode\n"));
	printf(_("  -t             turn on autocommit of transactions\n"));
	printf(_("  -V, --version  output version information, then exit\n"));
	printf(_("  -?, --help     show this help, then exit\n"));
	printf(_("\nIf no output file is specified, the name is formed by adding .c to the\n"
			 "input file name, after stripping off .pgc if present.\n"));
	printf(_("\nReport bugs to <pgsql-bugs@lists.postgresql.org>.\n"));
}