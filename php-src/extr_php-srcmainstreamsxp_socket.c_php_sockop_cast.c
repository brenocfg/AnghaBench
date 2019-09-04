#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mode; scalar_t__ abstract; } ;
typedef  TYPE_1__ php_stream ;
typedef  int /*<<< orphan*/  php_socket_t ;
struct TYPE_5__ {int /*<<< orphan*/  socket; } ;
typedef  TYPE_2__ php_netstream_data_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int FAILURE ; 
#define  PHP_STREAM_AS_FD 131 
#define  PHP_STREAM_AS_FD_FOR_SELECT 130 
#define  PHP_STREAM_AS_SOCKETD 129 
#define  PHP_STREAM_AS_STDIO 128 
 int SUCCESS ; 
 int /*<<< orphan*/ * fdopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_sockop_cast(php_stream *stream, int castas, void **ret)
{
	php_netstream_data_t *sock = (php_netstream_data_t*)stream->abstract;

	if (!sock) {
		return FAILURE;
	}

	switch(castas)	{
		case PHP_STREAM_AS_STDIO:
			if (ret)	{
				*(FILE**)ret = fdopen(sock->socket, stream->mode);
				if (*ret)
					return SUCCESS;
				return FAILURE;
			}
			return SUCCESS;
		case PHP_STREAM_AS_FD_FOR_SELECT:
		case PHP_STREAM_AS_FD:
		case PHP_STREAM_AS_SOCKETD:
			if (ret)
				*(php_socket_t *)ret = sock->socket;
			return SUCCESS;
		default:
			return FAILURE;
	}
}