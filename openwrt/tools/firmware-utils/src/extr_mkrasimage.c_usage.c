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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 

void usage(int status)
{
    FILE *stream = (status != EXIT_SUCCESS) ? stderr : stdout;

    fprintf(stream, "Usage: %s [OPTIONS...]\n", progname);
    fprintf(stream,
            "\n"
            "Options:\n"
            "  -k <kernel>     path for kernel image\n"
            "  -r <rootfs>     path for rootfs image\n"
            "  -s <rfssize>    size of output rootfs\n"
            "  -v <version>    version string\n"
            "  -b <boardname>  name of board to generate image for\n"
            "  -o <out_name>   name of output image\n"
            "  -l <hdr_length> length of header, default 65536\n"
            "  -h              show this screen\n"
    );

    exit(status);
}