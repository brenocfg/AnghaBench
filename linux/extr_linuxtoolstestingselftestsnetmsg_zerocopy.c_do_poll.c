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
struct pollfd {int events; int revents; int fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfg_waittime_ms ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int poll (struct pollfd*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_poll(int fd, int events)
{
	struct pollfd pfd;
	int ret;

	pfd.events = events;
	pfd.revents = 0;
	pfd.fd = fd;

	ret = poll(&pfd, 1, cfg_waittime_ms);
	if (ret == -1)
		error(1, errno, "poll");

	return ret && (pfd.revents & events);
}