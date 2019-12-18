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
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  appendfile (int,char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int open (char*,int,int) ; 
 char* output_file ; 
 int /*<<< orphan*/  parseopts (int*,char***) ; 
 int /*<<< orphan*/  signature ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*) ; 
 int /*<<< orphan*/  write (int,int /*<<< orphan*/ ,scalar_t__) ; 

int main(int argc, char **argv)
{
	int outfd;
	int i;

	parseopts(&argc, &argv);

	if (argc < 1)
		usage("wrong number of arguments");

	if ((outfd = open(output_file, O_WRONLY|O_CREAT|O_TRUNC, 0644)) == -1)
	{
		fprintf(stderr, "Error opening '%s' for writing: %s\n", output_file, strerror(errno));
		exit(1);
	}

	for (i=0; i<argc; i++) {
		appendfile(outfd, argv[i], i == 0);
	}
	write(outfd, signature, strlen(signature)+1);
	close(outfd);

	return 0;
}