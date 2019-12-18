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

__attribute__((used)) static int usage(int v) {
	printf ("Usage: ragg2 [-FOLsrxhvz] [-a arch] [-b bits] [-k os] [-o file] [-I path]\n"
		"             [-i sc] [-e enc] [-B hex] [-c k=v] [-C file] [-p pad] [-q off]\n"
		"             [-S string] [-f fmt] [-nN dword] [-dDw off:hex] file|f.asm|-\n");
	if (v) {
		printf (
			" -a [arch]       select architecture (x86, mips, arm)\n"
			" -b [bits]       register size (32, 64, ..)\n"
			" -B [hexpairs]   append some hexpair bytes\n"
			" -c [k=v]        set configuration options\n"
			" -C [file]       append contents of file\n"
			" -d [off:dword]  patch dword (4 bytes) at given offset\n"
			" -D [off:qword]  patch qword (8 bytes) at given offset\n"
			" -e [encoder]    use specific encoder. see -L\n"
			" -f [format]     output format (raw, c, pe, elf, mach0, python, javascript)\n"
			" -F              output native format (osx=mach0, linux=elf, ..)\n"
			" -h              show this help\n"
			" -i [shellcode]  include shellcode plugin, uses options. see -L\n"
			" -I [path]       add include path\n"
			" -k [os]         operating system's kernel (linux,bsd,osx,w32)\n"
			" -L              list all plugins (shellcodes and encoders)\n"
			" -n [dword]      append 32bit number (4 bytes)\n"
			" -N [dword]      append 64bit number (8 bytes)\n"
			" -o [file]       output file\n"
			" -O              use default output file (filename without extension or a.out)\n"
			" -p [padding]    add padding after compilation (padding=n10s32)\n"
			"                 ntas : begin nop, trap, 'a', sequence\n"
			"                 NTAS : same as above, but at the end\n"
			" -P [size]       prepend debruijn pattern\n"
			" -q [fragment]   debruijn pattern offset\n"
			" -r              show raw bytes instead of hexpairs\n"
			" -s              show assembler\n"
			" -S [string]     append a string\n"
			" -v              show version\n"
			" -w [off:hex]    patch hexpairs at given offset\n"
			" -x              execute\n"
			" -X [hexpairs]   execute rop chain, using the stack provided\n"
			" -z              output in C string syntax\n");
	}
	return 1;
}