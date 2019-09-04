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
 int O_APPEND ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int write (int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_kprobe_events(const char *val)
{
	int fd, ret, flags;

	if ((val != NULL) && (val[0] == '\0'))
		flags = O_WRONLY | O_TRUNC;
	else
		flags = O_WRONLY | O_APPEND;

	fd = open("/sys/kernel/debug/tracing/kprobe_events", flags);

	ret = write(fd, val, strlen(val));
	close(fd);

	return ret;
}