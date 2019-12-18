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

__attribute__((used)) static int do_help(int line) {
	printf ("Usage: rahash2 [-rBhLkv] [-b S] [-a A] [-c H] [-E A] [-s S] [-f O] [-t O] [file] ...\n");
	if (line) {
		return 0;
	}
	printf (
		" -a algo     comma separated list of algorithms (default is 'sha256')\n"
		" -b bsize    specify the size of the block (instead of full file)\n"
		" -B          show per-block hash\n"
		" -c hash     compare with this hash\n"
		" -e          swap endian (use little endian)\n"
		" -E algo     encrypt. Use -S to set key and -I to set IV\n"
		" -D algo     decrypt. Use -S to set key and -I to set IV\n"
		" -f from     start hashing at given address\n"
		" -i num      repeat hash N iterations\n"
		" -I iv       use give initialization vector (IV) (hexa or s:string)\n"
		" -S seed     use given seed (hexa or s:string) use ^ to prefix (key for -E)\n"
		"             (- will slurp the key from stdin, the @ prefix points to a file\n"
		" -k          show hash using the openssh's randomkey algorithm\n"
		" -q          run in quiet mode (-qq to show only the hash)\n"
		" -L          list all available algorithms (see -a)\n"
		" -r          output radare commands\n"
		" -s string   hash this string instead of files\n"
		" -t to       stop hashing at given address\n"
		" -x hexstr   hash this hexpair string instead of files\n"
		" -v          show version information\n");
	return 0;
}