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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  read (int,void*,int) ; 

__attribute__((used)) static void
get_random_bytes(void *ptr, int len)
{
	int fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0) {
		perror("open");
		exit(1);
	}
	read(fd, ptr, len);
	close(fd);
}