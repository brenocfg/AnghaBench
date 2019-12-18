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
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*,char*,char*,char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static void php_cli_usage(char *argv0)
{
	char *prog;

	prog = strrchr(argv0, '/');
	if (prog) {
		prog++;
	} else {
		prog = "php";
	}

	printf( "Usage: %s [options] [-f] <file> [--] [args...]\n"
				"   %s [options] -r <code> [--] [args...]\n"
				"   %s [options] [-B <begin_code>] -R <code> [-E <end_code>] [--] [args...]\n"
				"   %s [options] [-B <begin_code>] -F <file> [-E <end_code>] [--] [args...]\n"
				"   %s [options] -S <addr>:<port> [-t docroot] [router]\n"
				"   %s [options] -- [args...]\n"
				"   %s [options] -a\n"
				"\n"
#if (HAVE_LIBREADLINE || HAVE_LIBEDIT) && !defined(COMPILE_DL_READLINE)
				"  -a               Run as interactive shell\n"
#else
				"  -a               Run interactively\n"
#endif
				"  -c <path>|<file> Look for php.ini file in this directory\n"
				"  -n               No configuration (ini) files will be used\n"
				"  -d foo[=bar]     Define INI entry foo with value 'bar'\n"
				"  -e               Generate extended information for debugger/profiler\n"
				"  -f <file>        Parse and execute <file>.\n"
				"  -h               This help\n"
				"  -i               PHP information\n"
				"  -l               Syntax check only (lint)\n"
				"  -m               Show compiled in modules\n"
				"  -r <code>        Run PHP <code> without using script tags <?..?>\n"
				"  -B <begin_code>  Run PHP <begin_code> before processing input lines\n"
				"  -R <code>        Run PHP <code> for every input line\n"
				"  -F <file>        Parse and execute <file> for every input line\n"
				"  -E <end_code>    Run PHP <end_code> after processing all input lines\n"
				"  -H               Hide any passed arguments from external tools.\n"
				"  -S <addr>:<port> Run with built-in web server.\n"
				"  -t <docroot>     Specify document root <docroot> for built-in web server.\n"
				"  -s               Output HTML syntax highlighted source.\n"
				"  -v               Version number\n"
				"  -w               Output source with stripped comments and whitespace.\n"
				"  -z <file>        Load Zend extension <file>.\n"
				"\n"
				"  args...          Arguments passed to script. Use -- args when first argument\n"
				"                   starts with - or script is read from stdin\n"
				"\n"
				"  --ini            Show configuration file names\n"
				"\n"
				"  --rf <name>      Show information about function <name>.\n"
				"  --rc <name>      Show information about class <name>.\n"
				"  --re <name>      Show information about extension <name>.\n"
				"  --rz <name>      Show information about Zend extension <name>.\n"
				"  --ri <name>      Show configuration for extension <name>.\n"
				"\n"
				, prog, prog, prog, prog, prog, prog, prog);
}