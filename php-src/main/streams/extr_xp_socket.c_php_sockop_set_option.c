#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct timeval {int tv_sec; int /*<<< orphan*/  tv_usec; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_10__ {int returncode; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; int /*<<< orphan*/  textaddr; } ;
struct TYPE_9__ {int flags; int /*<<< orphan*/  buflen; int /*<<< orphan*/  buf; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; int /*<<< orphan*/  backlog; } ;
struct TYPE_11__ {size_t how; TYPE_2__ outputs; int /*<<< orphan*/  want_addr; int /*<<< orphan*/  want_textaddr; TYPE_1__ inputs; int /*<<< orphan*/  op; } ;
typedef  TYPE_3__ php_stream_xport_param ;
struct TYPE_12__ {int eof; scalar_t__ abstract; } ;
typedef  TYPE_4__ php_stream ;
struct TYPE_13__ {int socket; int is_blocked; int timeout_event; struct timeval timeout; } ;
typedef  TYPE_5__ php_netstream_data_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EAGAIN ; 
 int EMSGSIZE ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  E_WARNING ; 
 int FG (int /*<<< orphan*/ ) ; 
 int MSG_OOB ; 
 int MSG_PEEK ; 
 int PHP_POLLREADABLE ; 
#define  PHP_STREAM_OPTION_BLOCKING 141 
#define  PHP_STREAM_OPTION_CHECK_LIVENESS 140 
#define  PHP_STREAM_OPTION_META_DATA_API 139 
#define  PHP_STREAM_OPTION_READ_TIMEOUT 138 
 int PHP_STREAM_OPTION_RETURN_ERR ; 
 int PHP_STREAM_OPTION_RETURN_NOTIMPL ; 
 int PHP_STREAM_OPTION_RETURN_OK ; 
#define  PHP_STREAM_OPTION_XPORT_API 137 
 int POLLPRI ; 
#define  SHUT_RD 136 
#define  SHUT_RDWR 135 
#define  SHUT_WR 134 
 int STREAM_OOB ; 
 int STREAM_PEEK ; 
#define  STREAM_XPORT_OP_GET_NAME 133 
#define  STREAM_XPORT_OP_GET_PEER_NAME 132 
#define  STREAM_XPORT_OP_LISTEN 131 
#define  STREAM_XPORT_OP_RECV 130 
#define  STREAM_XPORT_OP_SEND 129 
#define  STREAM_XPORT_OP_SHUTDOWN 128 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  add_assoc_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  default_socket_timeout ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  listen (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int php_network_get_peer_name (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int php_network_get_sock_name (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_pollfd_for (int,int,struct timeval*) ; 
 int /*<<< orphan*/  php_set_sock_blocking (int,int) ; 
 int php_socket_errno () ; 
 char* php_socket_strerror (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recv (int,char*,int,int) ; 
 int shutdown (int,int const) ; 
 int sock_recvfrom (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sock_sendto (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_sockop_set_option(php_stream *stream, int option, int value, void *ptrparam)
{
	int oldmode, flags;
	php_netstream_data_t *sock = (php_netstream_data_t*)stream->abstract;
	php_stream_xport_param *xparam;

	if (!sock) {
		return PHP_STREAM_OPTION_RETURN_NOTIMPL;
	}

	switch(option) {
		case PHP_STREAM_OPTION_CHECK_LIVENESS:
			{
				struct timeval tv;
				char buf;
				int alive = 1;

				if (value == -1) {
					if (sock->timeout.tv_sec == -1) {
						tv.tv_sec = FG(default_socket_timeout);
						tv.tv_usec = 0;
					} else {
						tv = sock->timeout;
					}
				} else {
					tv.tv_sec = value;
					tv.tv_usec = 0;
				}

				if (sock->socket == -1) {
					alive = 0;
				} else if (php_pollfd_for(sock->socket, PHP_POLLREADABLE|POLLPRI, &tv) > 0) {
#ifdef PHP_WIN32
					int ret;
#else
					ssize_t ret;
#endif
					int err;

					ret = recv(sock->socket, &buf, sizeof(buf), MSG_PEEK);
					err = php_socket_errno();
					if (0 == ret || /* the counterpart did properly shutdown*/
						(0 > ret && err != EWOULDBLOCK && err != EAGAIN && err != EMSGSIZE)) { /* there was an unrecoverable error */
						alive = 0;
					}
				}
				return alive ? PHP_STREAM_OPTION_RETURN_OK : PHP_STREAM_OPTION_RETURN_ERR;
			}

		case PHP_STREAM_OPTION_BLOCKING:
			oldmode = sock->is_blocked;
			if (SUCCESS == php_set_sock_blocking(sock->socket, value)) {
				sock->is_blocked = value;
				return oldmode;
			}
			return PHP_STREAM_OPTION_RETURN_ERR;

		case PHP_STREAM_OPTION_READ_TIMEOUT:
			sock->timeout = *(struct timeval*)ptrparam;
			sock->timeout_event = 0;
			return PHP_STREAM_OPTION_RETURN_OK;

		case PHP_STREAM_OPTION_META_DATA_API:
			add_assoc_bool((zval *)ptrparam, "timed_out", sock->timeout_event);
			add_assoc_bool((zval *)ptrparam, "blocked", sock->is_blocked);
			add_assoc_bool((zval *)ptrparam, "eof", stream->eof);
			return PHP_STREAM_OPTION_RETURN_OK;

		case PHP_STREAM_OPTION_XPORT_API:
			xparam = (php_stream_xport_param *)ptrparam;

			switch (xparam->op) {
				case STREAM_XPORT_OP_LISTEN:
					xparam->outputs.returncode = (listen(sock->socket, xparam->inputs.backlog) == 0) ?  0: -1;
					return PHP_STREAM_OPTION_RETURN_OK;

				case STREAM_XPORT_OP_GET_NAME:
					xparam->outputs.returncode = php_network_get_sock_name(sock->socket,
							xparam->want_textaddr ? &xparam->outputs.textaddr : NULL,
							xparam->want_addr ? &xparam->outputs.addr : NULL,
							xparam->want_addr ? &xparam->outputs.addrlen : NULL
							);
					return PHP_STREAM_OPTION_RETURN_OK;

				case STREAM_XPORT_OP_GET_PEER_NAME:
					xparam->outputs.returncode = php_network_get_peer_name(sock->socket,
							xparam->want_textaddr ? &xparam->outputs.textaddr : NULL,
							xparam->want_addr ? &xparam->outputs.addr : NULL,
							xparam->want_addr ? &xparam->outputs.addrlen : NULL
							);
					return PHP_STREAM_OPTION_RETURN_OK;

				case STREAM_XPORT_OP_SEND:
					flags = 0;
					if ((xparam->inputs.flags & STREAM_OOB) == STREAM_OOB) {
						flags |= MSG_OOB;
					}
					xparam->outputs.returncode = sock_sendto(sock,
							xparam->inputs.buf, xparam->inputs.buflen,
							flags,
							xparam->inputs.addr,
							xparam->inputs.addrlen);
					if (xparam->outputs.returncode == -1) {
						char *err = php_socket_strerror(php_socket_errno(), NULL, 0);
						php_error_docref(NULL, E_WARNING,
						   	"%s\n", err);
						efree(err);
					}
					return PHP_STREAM_OPTION_RETURN_OK;

				case STREAM_XPORT_OP_RECV:
					flags = 0;
					if ((xparam->inputs.flags & STREAM_OOB) == STREAM_OOB) {
						flags |= MSG_OOB;
					}
					if ((xparam->inputs.flags & STREAM_PEEK) == STREAM_PEEK) {
						flags |= MSG_PEEK;
					}
					xparam->outputs.returncode = sock_recvfrom(sock,
							xparam->inputs.buf, xparam->inputs.buflen,
							flags,
							xparam->want_textaddr ? &xparam->outputs.textaddr : NULL,
							xparam->want_addr ? &xparam->outputs.addr : NULL,
							xparam->want_addr ? &xparam->outputs.addrlen : NULL
							);
					return PHP_STREAM_OPTION_RETURN_OK;


#ifdef HAVE_SHUTDOWN
# ifndef SHUT_RD
#  define SHUT_RD 0
# endif
# ifndef SHUT_WR
#  define SHUT_WR 1
# endif
# ifndef SHUT_RDWR
#  define SHUT_RDWR 2
# endif
				case STREAM_XPORT_OP_SHUTDOWN: {
					static const int shutdown_how[] = {SHUT_RD, SHUT_WR, SHUT_RDWR};

					xparam->outputs.returncode = shutdown(sock->socket, shutdown_how[xparam->how]);
					return PHP_STREAM_OPTION_RETURN_OK;
				}
#endif

				default:
					return PHP_STREAM_OPTION_RETURN_NOTIMPL;
			}

		default:
			return PHP_STREAM_OPTION_RETURN_NOTIMPL;
	}
}