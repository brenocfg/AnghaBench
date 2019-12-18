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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(const char *argv0) {
	fprintf(stderr,
		"Usage: %s [OPTIONS...]\n"
		"\n"
		"Options:\n"
		"  -h              show this help\n"
		"\n"
		"Create a new image:\n"
		"  -B <board>      create image for the board specified with <board>\n"
		"  -k <file>       read kernel image from the file <file>\n"
		"  -r <file>       read rootfs image from the file <file>\n"
		"  -o <file>       write output to the file <file>\n"
		"  -V <rev>        sets the revision number to <rev>\n"
		"  -j              add jffs2 end-of-filesystem markers\n"
		"  -S              create sysupgrade instead of factory image\n"
		"Extract an old image:\n"
		"  -x <file>       extract all oem firmware partition\n"
		"  -d <dir>        destination to extract the firmware partition\n"
		"  -z <file>       convert an oem firmware into a sysupgade file. Use -o for output file\n",
		argv0
	);
}