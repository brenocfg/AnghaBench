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
 int /*<<< orphan*/  O_RDWR ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  do_msg (int,int) ; 
 int /*<<< orphan*/  do_read (int,int) ; 
 int /*<<< orphan*/  dumpstat (char const*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getopt (int,char**,char*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  verbose ; 

int main(int argc, char **argv)
{
	int		c;
	int		readcount = 0;
	int		msglen = 0;
	int		fd;
	const char	*name;

	while ((c = getopt(argc, argv, "hm:r:v")) != EOF) {
		switch (c) {
		case 'm':
			msglen = atoi(optarg);
			if (msglen < 0)
				goto usage;
			continue;
		case 'r':
			readcount = atoi(optarg);
			if (readcount < 0)
				goto usage;
			continue;
		case 'v':
			verbose++;
			continue;
		case 'h':
		case '?':
usage:
			fprintf(stderr,
				"usage: %s [-h] [-m N] [-r N] /dev/spidevB.D\n",
				argv[0]);
			return 1;
		}
	}

	if ((optind + 1) != argc)
		goto usage;
	name = argv[optind];

	fd = open(name, O_RDWR);
	if (fd < 0) {
		perror("open");
		return 1;
	}

	dumpstat(name, fd);

	if (msglen)
		do_msg(fd, msglen);

	if (readcount)
		do_read(fd, readcount);

	close(fd);
	return 0;
}