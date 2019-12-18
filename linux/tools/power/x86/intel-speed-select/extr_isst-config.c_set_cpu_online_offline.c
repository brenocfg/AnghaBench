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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

__attribute__((used)) static void set_cpu_online_offline(int cpu, int state)
{
	char buffer[128];
	int fd;

	snprintf(buffer, sizeof(buffer),
		 "/sys/devices/system/cpu/cpu%d/online", cpu);

	fd = open(buffer, O_WRONLY);
	if (fd < 0)
		err(-1, "%s open failed", buffer);

	if (state)
		write(fd, "1\n", 2);
	else
		write(fd, "0\n", 2);

	close(fd);
}