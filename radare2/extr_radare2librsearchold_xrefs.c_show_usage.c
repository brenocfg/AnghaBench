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

__attribute__((used)) static int show_usage()
{
	printf(
	"Usage: xrefs [-options] [file] [offset]\n"
	" -v             Verbose mode\n"
	" -V             Show version\n"
	" -q             quite mode\n"
	" -h             Show this helpy message\n"
	" -e             Use big endian for offsets to search\n"
	" -a [arch]      Architecture profile (fmi: help) (autodetects ELF and PE hdrs)\n"
	" -b [address]   base address (0x8048000 f.ex)\n"
	" -f [from]      start scanning from this offset (default 0)\n"
	" -t [to]        limit address (default 99999999)\n"
	" -r [range]     Range in bytes of allowed relative offsets\n"
	" -s [size]      Size of offset (4 for intel, 3 for ppc, ...)\n"
	" -d [offset]    Sets a negative delta offset as padding (default 1)\n"
	" -X [offset]    Print out debugging information of a certain relative offset\n");

	return 1;
}