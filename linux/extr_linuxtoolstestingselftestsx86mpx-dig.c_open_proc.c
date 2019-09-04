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
 int /*<<< orphan*/  O_RDONLY ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char*) ; 

int open_proc(int pid, char *file)
{
	static char buf[100];
	int fd;

	snprintf(&buf[0], sizeof(buf), "/proc/%d/%s", pid, file);
	fd = open(&buf[0], O_RDONLY);
	if (fd < 0)
		perror(buf);

	return fd;
}