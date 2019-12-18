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
typedef  scalar_t__ uint ;
typedef  int ssize_t ;

/* Variables and functions */
 int read (int,char*,size_t) ; 

__attribute__((used)) static uint lines_in_file(int fd, char *buf, size_t buflen)
{
	ssize_t len;
	uint count = 0;

	while ((len = read(fd, buf, buflen)) > 0)
		while (len)
			count += (buf[--len] == '\n');

	/* For all use cases 0 linecount is considered as error */
	return ((len < 0) ? 0 : count);
}