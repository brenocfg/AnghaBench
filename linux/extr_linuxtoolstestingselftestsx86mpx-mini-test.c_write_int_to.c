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
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  assert (int) ; 
 int close (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char*,int) ; 
 int write (int,char*,int) ; 

void write_int_to(char *prefix, char *file, int int_to_write)
{
	char buf[100];
	int fd = open(file, O_RDWR);
	int len;
	int ret;

	assert(fd >= 0);
	len = snprintf(buf, sizeof(buf), "%s%d", prefix, int_to_write);
	assert(len >= 0);
	assert(len < sizeof(buf));
	ret = write(fd, buf, len);
	assert(ret == len);
	ret = close(fd);
	assert(!ret);
}