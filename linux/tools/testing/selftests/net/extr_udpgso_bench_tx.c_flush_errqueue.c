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
struct pollfd {int fd; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 scalar_t__ cfg_verbose ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  flush_errqueue_recv (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void flush_errqueue(int fd, const bool do_poll)
{
	if (do_poll) {
		struct pollfd fds = {0};
		int ret;

		fds.fd = fd;
		ret = poll(&fds, 1, 500);
		if (ret == 0) {
			if (cfg_verbose)
				fprintf(stderr, "poll timeout\n");
		} else if (ret < 0) {
			error(1, errno, "poll");
		}
	}

	flush_errqueue_recv(fd);
}