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
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int usage(void)
{
	fprintf(stderr,
		"Usage: %s file [<options>] [pad0] [pad1] [padN]\n"
		"Options:\n"
		"  -x <offset>:          Add an extra offset for padding data\n"
		"  -J:                   Use a fake big-endian jffs2 padding element instead of EOF\n"
		"                        This is used to work around broken boot loaders that\n"
		"                        try to parse the entire firmware area as one big jffs2\n"
		"  -j:                   (like -J, but little-endian instead of big-endian)\n"
		"  -c:                   write padding to stdout\n"
		"\n",
		progname);
	return EXIT_FAILURE;
}