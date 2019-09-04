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
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  v ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void term(int sig)
{
	int ret = write(fd, &v, 1);

	close(fd);
	if (ret < 0)
		printf("\nStopping watchdog ticks failed (%d)...\n", errno);
	else
		printf("\nStopping watchdog ticks...\n");
	exit(0);
}