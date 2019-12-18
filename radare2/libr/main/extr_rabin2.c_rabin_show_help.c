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

__attribute__((used)) static int rabin_show_help(int v) {
	printf ("Usage: rabin2 [-AcdeEghHiIjlLMqrRsSUvVxzZ] [-@ at] [-a arch] [-b bits] [-B addr]\n"
		"              [-C F:C:D] [-f str] [-m addr] [-n str] [-N m:M] [-P[-P] pdb]\n"
		"              [-o str] [-O str] [-k query] [-D lang symname] file\n");
	if (v) {
		printf (
		" -@ [addr]       show section, symbol or import at addr\n"
		" -A              list sub-binaries and their arch-bits pairs\n"
		" -a [arch]       set arch (x86, arm, .. or <arch>_<bits>)\n"
		" -b [bits]       set bits (32, 64 ...)\n"
		" -B [addr]       override base address (pie bins)\n"
		" -c              list classes\n"
		" -cc             list classes in header format\n"
		" -C [fmt:C:D]    create [elf,mach0,pe] with Code and Data hexpairs (see -a)\n"
		" -d              show debug/dwarf information\n"
		" -D lang name    demangle symbol name (-D all for bin.demangle=true)\n"
		" -e              entrypoint\n"
		" -ee             constructor/destructor entrypoints\n"
		" -E              globally exportable symbols\n"
		" -f [str]        select sub-bin named str\n"
		" -F [binfmt]     force to use that bin plugin (ignore header check)\n"
		" -g              same as -SMZIHVResizcld -SS -ee (show all info)\n"
		" -G [addr]       load address . offset to header\n"
		" -h              this help message\n"
		" -H              header fields\n"
		" -i              imports (symbols imported from libraries)\n"
		" -I              binary info\n"
		" -j              output in json\n"
		" -k [sdb-query]  run sdb query. for example: '*'\n"
		" -K [algo]       calculate checksums (md5, sha1, ..)\n"
		" -l              linked libraries\n"
		" -L [plugin]     list supported bin plugins or plugin details\n"
		" -m [addr]       show source line at addr\n"
		" -M              main (show address of main symbol)\n"
		" -n [str]        show section, symbol or import named str\n"
		" -N [min:max]    force min:max number of chars per string (see -z and -zz)\n"
		" -o [str]        output file/folder for write operations (out by default)\n"
		" -O [str]        write/extract operations (-O help)\n"
		" -p              show physical addresses\n"
		" -P              show debug/pdb information\n"
		" -PP             download pdb file for binary\n"
		" -q              be quiet, just show fewer data\n"
		" -qq             show less info (no offset/size for -z for ex.)\n"
		" -Q              show load address used by dlopen (non-aslr libs)\n"
		" -r              radare output\n"
		" -R              relocations\n"
		" -s              symbols\n"
		" -S              sections\n"
		" -SS             segments\n"
		" -t              display file hashes\n"
		" -T              display file signature\n"
		" -u              unfiltered (no rename duplicated symbols/sections)\n"
		" -U              resoUrces\n"
		" -v              display version and quit\n"
		" -V              Show binary version information\n"
		" -w              display try/catch blocks\n"
		" -x              extract bins contained in file\n"
		" -X [fmt] [f] .. package in fat or zip the given files and bins contained in file\n"
		" -z              strings (from data section)\n"
		" -zz             strings (from raw bins [e bin.rawstr=1])\n"
		" -zzz            dump raw strings to stdout (for huge files)\n"
		" -Z              guess size of binary program\n"
		);
	}
	if (v) {
		printf ("Environment:\n"
		" RABIN2_LANG:      e bin.lang         # assume lang for demangling\n"
		" RABIN2_NOPLUGINS: # do not load shared plugins (speedup loading)\n"
		" RABIN2_DEMANGLE=0:e bin.demangle     # do not demangle symbols\n"
		" RABIN2_MAXSTRBUF: e bin.maxstrbuf    # specify maximum buffer size\n"
		" RABIN2_STRFILTER: e bin.str.filter   #  r2 -qc 'e bin.str.filter=?" "?' -\n"
		" RABIN2_STRPURGE:  e bin.str.purge    # try to purge false positives\n"
		" RABIN2_DEBASE64:  e bin.debase64     # try to debase64 all strings\n"
		" RABIN2_DMNGLRCMD: e bin.demanglercmd # try to purge false positives\n"
		" RABIN2_PDBSERVER: e pdb.server       # use alternative PDB server\n"
		" RABIN2_SYMSTORE:  e pdb.symstore     # path to downstream symbol store\n"
		" RABIN2_PREFIX:    e bin.prefix       # prefix symbols/sections/relocs with a specific string\n");
	}
	return 1;
}