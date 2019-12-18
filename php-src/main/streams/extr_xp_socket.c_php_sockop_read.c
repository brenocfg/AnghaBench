#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_9__ {int eof; scalar_t__ abstract; } ;
typedef  TYPE_2__ php_stream ;
struct TYPE_8__ {int tv_sec; } ;
struct TYPE_10__ {int socket; TYPE_1__ timeout; scalar_t__ is_blocked; scalar_t__ timeout_event; } ;
typedef  TYPE_3__ php_netstream_data_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int /*<<< orphan*/  PHP_STREAM_CONTEXT (TYPE_2__*) ; 
 int /*<<< orphan*/  XP_SOCK_BUF_SIZE (size_t) ; 
 int /*<<< orphan*/  php_sock_stream_wait_for_data (TYPE_2__*,TYPE_3__*) ; 
 int php_socket_errno () ; 
 int /*<<< orphan*/  php_stream_notify_progress_increment (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int recv (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t php_sockop_read(php_stream *stream, char *buf, size_t count)
{
	php_netstream_data_t *sock = (php_netstream_data_t*)stream->abstract;
	ssize_t nr_bytes = 0;
	int err;

	if (!sock || sock->socket == -1) {
		return -1;
	}

	if (sock->is_blocked) {
		php_sock_stream_wait_for_data(stream, sock);
		if (sock->timeout_event)
			return 0;
	}

	nr_bytes = recv(sock->socket, buf, XP_SOCK_BUF_SIZE(count), (sock->is_blocked && sock->timeout.tv_sec != -1) ? MSG_DONTWAIT : 0);
	err = php_socket_errno();

	if (nr_bytes < 0) {
		if (err == EAGAIN || err == EWOULDBLOCK) {
			nr_bytes = 0;
		} else {
			stream->eof = 1;
		}
	} else if (nr_bytes == 0) {
		stream->eof = 1;
	}

	if (nr_bytes > 0) {
		php_stream_notify_progress_increment(PHP_STREAM_CONTEXT(stream), nr_bytes, 0);
	}

	return nr_bytes;
}