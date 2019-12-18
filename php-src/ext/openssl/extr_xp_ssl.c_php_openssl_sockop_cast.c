#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t chunk_size; int /*<<< orphan*/  readpos; int /*<<< orphan*/  writepos; int /*<<< orphan*/  mode; scalar_t__ abstract; } ;
typedef  TYPE_2__ php_stream ;
typedef  int /*<<< orphan*/  php_socket_t ;
struct TYPE_6__ {int /*<<< orphan*/  socket; } ;
struct TYPE_8__ {TYPE_1__ s; int /*<<< orphan*/  ssl_active; int /*<<< orphan*/  ssl_handle; } ;
typedef  TYPE_3__ php_openssl_netstream_data_t ;

/* Variables and functions */
 int FAILURE ; 
#define  PHP_STREAM_AS_FD 131 
#define  PHP_STREAM_AS_FD_FOR_SELECT 130 
#define  PHP_STREAM_AS_SOCKETD 129 
#define  PHP_STREAM_AS_STDIO 128 
 int /*<<< orphan*/  SSL_pending (int /*<<< orphan*/ ) ; 
 int SUCCESS ; 
 void* fdopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_fill_read_buffer (TYPE_2__*,size_t) ; 

__attribute__((used)) static int php_openssl_sockop_cast(php_stream *stream, int castas, void **ret)  /* {{{ */
{
	php_openssl_netstream_data_t *sslsock = (php_openssl_netstream_data_t*)stream->abstract;

	switch(castas)	{
		case PHP_STREAM_AS_STDIO:
			if (sslsock->ssl_active) {
				return FAILURE;
			}
			if (ret)	{
				*ret = fdopen(sslsock->s.socket, stream->mode);
				if (*ret) {
					return SUCCESS;
				}
				return FAILURE;
			}
			return SUCCESS;

		case PHP_STREAM_AS_FD_FOR_SELECT:
			if (ret) {
				size_t pending;
				if (stream->writepos == stream->readpos
					&& sslsock->ssl_active
					&& (pending = (size_t)SSL_pending(sslsock->ssl_handle)) > 0) {
						php_stream_fill_read_buffer(stream, pending < stream->chunk_size
							? pending
							: stream->chunk_size);
				}

				*(php_socket_t *)ret = sslsock->s.socket;
			}
			return SUCCESS;

		case PHP_STREAM_AS_FD:
		case PHP_STREAM_AS_SOCKETD:
			if (sslsock->ssl_active) {
				return FAILURE;
			}
			if (ret) {
				*(php_socket_t *)ret = sslsock->s.socket;
			}
			return SUCCESS;
		default:
			return FAILURE;
	}
}