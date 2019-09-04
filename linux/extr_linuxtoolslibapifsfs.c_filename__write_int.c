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
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int write (int,char*,int) ; 

int filename__write_int(const char *filename, int value)
{
	int fd = open(filename, O_WRONLY), err = -1;
	char buf[64];

	if (fd < 0)
		return err;

	sprintf(buf, "%d", value);
	if (write(fd, buf, sizeof(buf)) == sizeof(buf))
		err = 0;

	close(fd);
	return err;
}