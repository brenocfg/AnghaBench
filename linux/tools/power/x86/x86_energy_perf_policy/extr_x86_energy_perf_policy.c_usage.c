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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 

void usage(void)
{
	fprintf(stderr, "%s [options] [scope][field value]\n", progname);
	fprintf(stderr, "scope: --cpu cpu-list [--hwp-use-pkg #] | --pkg pkg-list\n");
	fprintf(stderr, "field: --all | --epb | --hwp-epp | --hwp-min | --hwp-max | --hwp-desired\n");
	fprintf(stderr, "other: --hwp-enable | --turbo-enable (0 | 1) | --help | --force\n");
	fprintf(stderr,
		"value: ( # | \"normal\" | \"performance\" | \"balance-performance\" | \"balance-power\"| \"power\")\n");
	fprintf(stderr, "--hwp-window usec\n");

	fprintf(stderr, "Specify only Energy Performance BIAS (legacy usage):\n");
	fprintf(stderr, "%s: [-c cpu] [-v] (-r | policy-value )\n", progname);

	exit(1);
}