#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_12__ {int error_code; int /*<<< orphan*/  error_text; } ;
struct TYPE_11__ {int /*<<< orphan*/  timeout; } ;
struct TYPE_13__ {scalar_t__ op; TYPE_2__ outputs; int /*<<< orphan*/  want_errortext; TYPE_1__ inputs; } ;
typedef  TYPE_3__ php_stream_xport_param ;
struct TYPE_14__ {int /*<<< orphan*/ * ops; } ;
typedef  TYPE_4__ php_stream ;
struct TYPE_15__ {int socket; } ;
typedef  TYPE_5__ php_netstream_data_t ;

/* Variables and functions */
 int EINPROGRESS ; 
 scalar_t__ IS_STRING ; 
 scalar_t__ PHP_STREAM_CONTEXT (TYPE_4__*) ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 long STREAM_SOCKOP_NONE ; 
 long STREAM_SOCKOP_TCP_NODELAY ; 
 scalar_t__ STREAM_XPORT_OP_CONNECT_ASYNC ; 
 int /*<<< orphan*/  Z_STRLEN_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* parse_ip_address (TYPE_3__*,int*) ; 
 char* parse_ip_address_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int php_network_connect_socket_to_host (char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,char*,int,long) ; 
 int /*<<< orphan*/ * php_stream_context_get_option (scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  php_stream_udp_socket_ops ; 
 int /*<<< orphan*/  strpprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ zend_is_true (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int php_tcp_sockop_connect(php_stream *stream, php_netstream_data_t *sock,
		php_stream_xport_param *xparam)
{
	char *host = NULL, *bindto = NULL;
	int portno, bindport = 0;
	int err = 0;
	int ret;
	zval *tmpzval = NULL;
	long sockopts = STREAM_SOCKOP_NONE;

#ifdef AF_UNIX
	if (stream->ops == &php_stream_unix_socket_ops || stream->ops == &php_stream_unixdg_socket_ops) {
		struct sockaddr_un unix_addr;

		sock->socket = socket(PF_UNIX, stream->ops == &php_stream_unix_socket_ops ? SOCK_STREAM : SOCK_DGRAM, 0);

		if (sock->socket == SOCK_ERR) {
			if (xparam->want_errortext) {
				xparam->outputs.error_text = strpprintf(0, "Failed to create unix socket");
			}
			return -1;
		}

		parse_unix_address(xparam, &unix_addr);

		ret = php_network_connect_socket(sock->socket,
				(const struct sockaddr *)&unix_addr, (socklen_t) XtOffsetOf(struct sockaddr_un, sun_path) + xparam->inputs.namelen,
				xparam->op == STREAM_XPORT_OP_CONNECT_ASYNC, xparam->inputs.timeout,
				xparam->want_errortext ? &xparam->outputs.error_text : NULL,
				&err);

		xparam->outputs.error_code = err;

		goto out;
	}
#endif

	host = parse_ip_address(xparam, &portno);

	if (host == NULL) {
		return -1;
	}

	if (PHP_STREAM_CONTEXT(stream) && (tmpzval = php_stream_context_get_option(PHP_STREAM_CONTEXT(stream), "socket", "bindto")) != NULL) {
		if (Z_TYPE_P(tmpzval) != IS_STRING) {
			if (xparam->want_errortext) {
				xparam->outputs.error_text = strpprintf(0, "local_addr context option is not a string.");
			}
			efree(host);
			return -1;
		}
		bindto = parse_ip_address_ex(Z_STRVAL_P(tmpzval), Z_STRLEN_P(tmpzval), &bindport, xparam->want_errortext, &xparam->outputs.error_text);
	}

#ifdef SO_BROADCAST
	if (stream->ops == &php_stream_udp_socket_ops /* SO_BROADCAST is only applicable for UDP */
		&& PHP_STREAM_CONTEXT(stream)
		&& (tmpzval = php_stream_context_get_option(PHP_STREAM_CONTEXT(stream), "socket", "so_broadcast")) != NULL
		&& zend_is_true(tmpzval)
	) {
		sockopts |= STREAM_SOCKOP_SO_BROADCAST;
	}
#endif

	if (stream->ops != &php_stream_udp_socket_ops /* TCP_NODELAY is only applicable for TCP */
#ifdef AF_UNIX
		&& stream->ops != &php_stream_unix_socket_ops
		&& stream->ops != &php_stream_unixdg_socket_ops
#endif
		&& PHP_STREAM_CONTEXT(stream)
		&& (tmpzval = php_stream_context_get_option(PHP_STREAM_CONTEXT(stream), "socket", "tcp_nodelay")) != NULL
		&& zend_is_true(tmpzval)
	) {
		sockopts |= STREAM_SOCKOP_TCP_NODELAY;
	}

	/* Note: the test here for php_stream_udp_socket_ops is important, because we
	 * want the default to be TCP sockets so that the openssl extension can
	 * re-use this code. */

	sock->socket = php_network_connect_socket_to_host(host, portno,
			stream->ops == &php_stream_udp_socket_ops ? SOCK_DGRAM : SOCK_STREAM,
			xparam->op == STREAM_XPORT_OP_CONNECT_ASYNC,
			xparam->inputs.timeout,
			xparam->want_errortext ? &xparam->outputs.error_text : NULL,
			&err,
			bindto,
			bindport,
			sockopts
			);

	ret = sock->socket == -1 ? -1 : 0;
	xparam->outputs.error_code = err;

	if (host) {
		efree(host);
	}
	if (bindto) {
		efree(bindto);
	}

#ifdef AF_UNIX
out:
#endif

	if (ret >= 0 && xparam->op == STREAM_XPORT_OP_CONNECT_ASYNC && err == EINPROGRESS) {
		/* indicates pending connection */
		return 1;
	}

	return ret;
}