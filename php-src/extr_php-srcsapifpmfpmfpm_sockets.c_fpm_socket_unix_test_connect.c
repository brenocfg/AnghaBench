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
struct sockaddr_un {scalar_t__ sun_family; } ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_UNIX ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr*,size_t) ; 
 int socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int fpm_socket_unix_test_connect(struct sockaddr_un *sock, size_t socklen) /* {{{ */
{
	int fd;

	if (!sock || sock->sun_family != AF_UNIX) {
		return -1;
	}

	if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
		return -1;
	}

	if (connect(fd, (struct sockaddr *)sock, socklen) == -1) {
		close(fd);
		return -1;
	}

	close(fd);
	return 0;
}