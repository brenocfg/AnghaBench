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
 int /*<<< orphan*/  DSCR_DEFAULT ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int write (int,char*,int /*<<< orphan*/ ) ; 

void set_default_dscr(unsigned long val)
{
	int fd = -1, ret;
	char buf[16];

	if (fd == -1) {
		fd = open(DSCR_DEFAULT, O_RDWR);
		if (fd == -1) {
			perror("open() failed");
			exit(1);
		}
	}
	sprintf(buf, "%lx\n", val);
	ret = write(fd, buf, strlen(buf));
	if (ret == -1) {
		perror("write() failed");
		exit(1);
	}
	close(fd);
}