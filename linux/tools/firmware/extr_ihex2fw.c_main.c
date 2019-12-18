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
typedef  int /*<<< orphan*/  uint8_t ;
struct stat {int /*<<< orphan*/  st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/ * MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int O_CREAT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int getopt (int,char**,char*) ; 
 int include_jump ; 
 int /*<<< orphan*/ * mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int open (char*,int,...) ; 
 int optind ; 
 int output_records (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ process_ihex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sort_records ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int usage () ; 
 int wide_records ; 

int main(int argc, char **argv)
{
	int infd, outfd;
	struct stat st;
	uint8_t *data;
	int opt;

	while ((opt = getopt(argc, argv, "wsj")) != -1) {
		switch (opt) {
		case 'w':
			wide_records = 1;
			break;
		case 's':
			sort_records = 1;
			break;
		case 'j':
			include_jump = 1;
			break;
		default:
			return usage();
		}
	}

	if (optind + 2 != argc)
		return usage();

	if (!strcmp(argv[optind], "-"))
		infd = 0;
	else
		infd = open(argv[optind], O_RDONLY);
	if (infd == -1) {
		fprintf(stderr, "Failed to open source file: %s",
			strerror(errno));
		return usage();
	}
	if (fstat(infd, &st)) {
		perror("stat");
		return 1;
	}
	data = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, infd, 0);
	if (data == MAP_FAILED) {
		perror("mmap");
		return 1;
	}

	if (!strcmp(argv[optind+1], "-"))
		outfd = 1;
	else
		outfd = open(argv[optind+1], O_TRUNC|O_CREAT|O_WRONLY, 0644);
	if (outfd == -1) {
		fprintf(stderr, "Failed to open destination file: %s",
			strerror(errno));
		return usage();
	}
	if (process_ihex(data, st.st_size))
		return 1;

	return output_records(outfd);
}