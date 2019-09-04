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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  DSCR_DEFAULT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  sscanf (char*,char*,unsigned long*) ; 

unsigned long get_default_dscr(void)
{
	int fd = -1, ret;
	char buf[16];
	unsigned long val;

	if (fd == -1) {
		fd = open(DSCR_DEFAULT, O_RDONLY);
		if (fd == -1) {
			perror("open() failed");
			exit(1);
		}
	}
	memset(buf, 0, sizeof(buf));
	lseek(fd, 0, SEEK_SET);
	ret = read(fd, buf, sizeof(buf));
	if (ret == -1) {
		perror("read() failed");
		exit(1);
	}
	sscanf(buf, "%lx", &val);
	close(fd);
	return val;
}