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
 int EOF ; 
 int dump_devices () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int getopt (int,char**,char*) ; 
 int optind ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  verblevel ; 

int main(int argc, char **argv)
{
	int c, err = 0;

	while ((c = getopt(argc, argv, "v")) != EOF) {
		switch (c) {
		case 'v':
			verblevel++;
			break;

		case '?':
		default:
			err++;
			break;
		}
	}
	if (err || argc > optind) {
		fprintf(stderr, "Usage: lsiio [options]...\n"
			"List industrial I/O devices\n"
			"  -v  Increase verbosity (may be given multiple times)\n");
		exit(1);
	}

	return dump_devices();
}