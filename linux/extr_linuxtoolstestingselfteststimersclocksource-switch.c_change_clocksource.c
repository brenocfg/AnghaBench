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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ write (int,char*,int /*<<< orphan*/ ) ; 

int change_clocksource(char *clocksource)
{
	int fd;
	ssize_t size;

	fd = open("/sys/devices/system/clocksource/clocksource0/current_clocksource", O_WRONLY);

	if (fd < 0)
		return -1;

	size = write(fd, clocksource, strlen(clocksource));

	if (size < 0)
		return -1;

	close(fd);
	return 0;
}