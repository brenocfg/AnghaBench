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
 int STDERR_FILENO ; 
 int /*<<< orphan*/  TIOCSCTTY ; 
 int /*<<< orphan*/  close (int) ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setsid () ; 
 int terminal_set_stdfds (int) ; 

__attribute__((used)) static int login_pty(int fd)
{
	int ret;

	setsid();

	ret = ioctl(fd, TIOCSCTTY, NULL);
	if (ret < 0)
		return -1;

	ret = terminal_set_stdfds(fd);
	if (ret < 0)
		return -1;

	if (fd > STDERR_FILENO)
		close(fd);

	return 0;
}