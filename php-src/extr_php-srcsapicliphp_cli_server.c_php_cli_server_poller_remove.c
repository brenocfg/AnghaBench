#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ php_socket_t ;
struct TYPE_3__ {scalar_t__ max_fd; int /*<<< orphan*/  wfds; int /*<<< orphan*/  rfds; } ;
typedef  TYPE_1__ php_cli_server_poller ;

/* Variables and functions */
 int /*<<< orphan*/  PHP_SAFE_FD_CLR (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ PHP_SAFE_FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 int POLLIN ; 
 int POLLOUT ; 

__attribute__((used)) static void php_cli_server_poller_remove(php_cli_server_poller *poller, int mode, php_socket_t fd) /* {{{ */
{
	if (mode & POLLIN) {
		PHP_SAFE_FD_CLR(fd, &poller->rfds);
	}
	if (mode & POLLOUT) {
		PHP_SAFE_FD_CLR(fd, &poller->wfds);
	}
#ifndef PHP_WIN32
	if (fd == poller->max_fd) {
		while (fd > 0) {
			fd--;
			if (PHP_SAFE_FD_ISSET(fd, &poller->rfds) || PHP_SAFE_FD_ISSET(fd, &poller->wfds)) {
				break;
			}
		}
		poller->max_fd = fd;
	}
#endif
}