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
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  SIGINT ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ender ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  measure (int) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char **argv)
{
    int fd;
    char *disk = 0;
    int settle_time = 60;

    /* Parse the simple command-line */
    if (argc == 2)
	disk = argv[1];
    else if (argc == 4) {
	settle_time = atoi(argv[2]);
	disk = argv[3];
    } else
	usage();

    if (!(fd = open(disk, O_RDONLY|O_NONBLOCK))) {
	printf("Can't open %s, because: %s\n", disk, strerror(errno));
	exit(-1);
    }

    if (settle_time) {
	printf("Waiting %d seconds for the system to settle down to "
	       "'normal'\n", settle_time);
	sleep(settle_time);
    } else
	puts("Not waiting for system to settle down");

    signal(SIGINT, ender);

    measure(fd);

    close(fd);

    return 0;
}