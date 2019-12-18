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
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int show_help(int v) {
	printf ("Usage: radiff2 [-abBcCdjrspOxuUvV] [-A[A]] [-g sym] [-m graph_mode][-t %%] [file] [file]\n");
	if (v) {
		printf (
			"  -a [arch]  specify architecture plugin to use (x86, arm, ..)\n"
			"  -A [-A]    run aaa or aaaa after loading each binary (see -C)\n"
			"  -b [bits]  specify register size for arch (16 (thumb), 32, 64, ..)\n"
			"  -B         output in binary diff (GDIFF)\n"
			"  -c         count of changes\n"
			"  -C         graphdiff code (columns: off-A, match-ratio, off-B) (see -A)\n"
			"  -d         use delta diffing\n"
			"  -D         show disasm instead of hexpairs\n"
			"  -e [k=v]   set eval config var value for all RCore instances\n"
			"  -g [sym|off1,off2]   graph diff of given symbol, or between two offsets\n"
			"  -G [cmd]   run an r2 command on every RCore instance created\n"
			"  -i         diff imports of target files (see -u, -U and -z)\n"
			"  -j         output in json format\n"
			"  -n         print bare addresses only (diff.bare=1)\n"
                        "  -m [aditsjJ]  choose the graph output mode\n"
			"  -O         code diffing with opcode bytes only\n"
			"  -p         use physical addressing (io.va=0)\n"
			"  -q         quiet mode (disable colors, reduce output)\n"
			"  -r         output in radare commands\n"
			"  -s         compute edit distance (no substitution, Eugene W. Myers' O(ND) diff algorithm)\n"
			"  -ss        compute Levenshtein edit distance (substitution is allowed, O(N^2))\n"
			"  -S [name]  sort code diff (name, namelen, addr, size, type, dist) (only for -C or -g)\n"
			"  -t [0-100] set threshold for code diff (default is 70%%)\n"
			"  -x         show two column hexdump diffing\n"
			"  -X         show two column hexII diffing\n"
			"  -u         unified output (---+++)\n"
			"  -U         unified output using system 'diff'\n"
			"  -v         show version information\n"
			"  -V         be verbose (current only for -s)\n"
			"  -z         diff on extracted strings\n"
			"  -Z         diff code comparing zignatures\n\n"
                       "Graph Output formats: (-m [mode])\n"
		        "  <blank/a>  Ascii art\n"
	                "  s          r2 commands\n"
		        "  d          Graphviz dot\n"
	                "  g          Graph Modelling Language (gml)\n"
		        "  j          json\n"
	                "  J          json with disarm\n"
		        "  k          SDB key-value\n"
	                "  t          Tiny ascii art\n"
		        "  i          Interactive ascii art\n");
	}
	return 1;
}