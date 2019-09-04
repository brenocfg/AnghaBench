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
typedef  int ssize_t ;

/* Variables and functions */
 int O_APPEND ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char const*,int) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static ssize_t write_text(const char *path, char *buf, ssize_t len)
{
	int fd;

	fd = open(path, O_WRONLY | O_APPEND);
	if (fd < 0)
		return fd;

	len = write(fd, buf, len);
	if (len < 0) {
		close(fd);
		return len;
	}

	close(fd);

	return len;
}