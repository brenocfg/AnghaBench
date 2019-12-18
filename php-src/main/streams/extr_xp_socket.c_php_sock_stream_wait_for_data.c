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
struct timeval {int tv_sec; } ;
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_3__ {int socket; int timeout_event; struct timeval timeout; } ;
typedef  TYPE_1__ php_netstream_data_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  PHP_POLLREADABLE ; 
 int php_pollfd_for (int,int /*<<< orphan*/ ,struct timeval*) ; 
 scalar_t__ php_socket_errno () ; 

__attribute__((used)) static void php_sock_stream_wait_for_data(php_stream *stream, php_netstream_data_t *sock)
{
	int retval;
	struct timeval *ptimeout;

	if (!sock || sock->socket == -1) {
		return;
	}

	sock->timeout_event = 0;

	if (sock->timeout.tv_sec == -1)
		ptimeout = NULL;
	else
		ptimeout = &sock->timeout;

	while(1) {
		retval = php_pollfd_for(sock->socket, PHP_POLLREADABLE, ptimeout);

		if (retval == 0)
			sock->timeout_event = 1;

		if (retval >= 0)
			break;

		if (php_socket_errno() != EINTR)
			break;
	}
}