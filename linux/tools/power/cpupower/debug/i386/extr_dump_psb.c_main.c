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
 int LEN ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  decode_psb (char*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  info_opts ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 char* mmap (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  munmap (char*,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  print_help () ; 
 int /*<<< orphan*/  printf (char*) ; 
 void* relevant ; 
 void* strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int
main(int argc, char *argv[])
{
	int fd;
	int numpst=-1;
	int ret=0, cont=1;
	char *mem = NULL;
	char *p;

	do {
		ret = getopt_long(argc, argv, "hr:n:", info_opts, NULL);
		switch (ret){
		case '?':
		case 'h':
			print_help();
			cont = 0;
			break;
		case 'r':
			relevant = strtol(optarg, NULL, 16);
			break;
		case 'n':
			numpst = strtol(optarg, NULL, 10);
			break;
		case -1:
			cont = 0;
			break;
		}

	} while(cont);

	fd = open("/dev/mem", O_RDONLY);
	if (fd < 0) {
		printf ("Couldn't open /dev/mem. Are you root?\n");
		exit(1);
	}

	mem = mmap(mem, 0x100000 - 0xc0000, PROT_READ, MAP_SHARED, fd, 0xc0000);
	close(fd);

	for (p = mem; p - mem < LEN; p+=16) {
		if (memcmp(p, "AMDK7PNOW!", 10) == 0) {
			decode_psb(p, numpst);
			break;
		}
	}

	munmap(mem, LEN);
	return 0;
}