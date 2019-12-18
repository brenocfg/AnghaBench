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
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int show_help(char *argv0, int line) {
	printf ("Usage: %s [-mXnzZhqv] [-a align] [-b sz] [-f/t from/to] [-[e|s|S] str] [-x hex] -|file|dir ..\n", argv0);
	if (line) {
		return 0;
	}
	printf (
	" -a [align] only accept aligned hits\n"
	" -b [size]  set block size\n"
	" -e [regex] search for regex matches (can be used multiple times)\n"
	" -f [from]  start searching from address 'from'\n"
	" -h         show this help\n"
	" -i         identify filetype (r2 -nqcpm file)\n"
	" -j         output in JSON\n"
	" -m         magic search, file-type carver\n"
	" -M [str]   set a binary mask to be applied on keywords\n"
	" -n         do not stop on read errors\n"
	" -r         print using radare commands\n"
	" -s [str]   search for a specific string (can be used multiple times)\n"
	" -S [str]   search for a specific wide string (can be used multiple times). Assumes str is UTF-8.\n"
	" -t [to]    stop search at address 'to'\n"
	" -q         quiet - do not show headings (filenames) above matching contents (default for searching a single file)\n"
	" -v         print version and exit\n"
	" -x [hex]   search for hexpair string (909090) (can be used multiple times)\n"
	" -X         show hexdump of search results\n"
	" -z         search for zero-terminated strings\n"
	" -Z         show string found on each search hit\n"
	);
	return 0;
}