#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_10__ {scalar_t__ activate; } ;
struct TYPE_11__ {TYPE_2__ inputs; } ;
typedef  TYPE_3__ php_stream_xport_crypto_param ;
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_9__ {int is_blocked; int /*<<< orphan*/  socket; struct timeval timeout; } ;
struct TYPE_12__ {int ssl_active; int state_set; int /*<<< orphan*/  ssl_handle; TYPE_1__ s; scalar_t__ is_client; struct timeval connect_timeout; } ;
typedef  TYPE_4__ php_openssl_netstream_data_t ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  E_DEPRECATED ; 
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ FAILURE ; 
 scalar_t__ PHP_STREAM_CONTEXT (int /*<<< orphan*/ *) ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLPRI ; 
 int SSL_ERROR_WANT_READ ; 
 int SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER ; 
 int SSL_MODE_ENABLE_PARTIAL_WRITE ; 
 int SSL_accept (int /*<<< orphan*/ ) ; 
 int SSL_connect (int /*<<< orphan*/ ) ; 
 int SSL_get_error (int /*<<< orphan*/ ,int) ; 
 int SSL_get_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SSL_get_peer_certificate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_accept_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_connect_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_mode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_ARR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ php_openssl_apply_peer_verification_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int php_openssl_capture_peer_certs (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_openssl_capture_session_meta (int /*<<< orphan*/ ) ; 
 scalar_t__ php_openssl_compare_timeval (struct timeval,struct timeval) ; 
 int /*<<< orphan*/  php_openssl_enable_client_sni (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int php_openssl_handle_ssl_error (int /*<<< orphan*/ *,int,int) ; 
 struct timeval php_openssl_subtract_timeval (struct timeval,struct timeval) ; 
 int /*<<< orphan*/  php_pollfd_for (int /*<<< orphan*/ ,int,struct timeval*) ; 
 scalar_t__ php_set_sock_blocking (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * php_stream_context_get_option (scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  php_stream_context_set_option (scalar_t__,char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ zend_is_true (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int php_openssl_enable_crypto(php_stream *stream,
		php_openssl_netstream_data_t *sslsock,
		php_stream_xport_crypto_param *cparam) /* {{{ */
{
	int n;
	int retry = 1;
	int cert_captured = 0;
	X509 *peer_cert;

	if (cparam->inputs.activate && !sslsock->ssl_active) {
		struct timeval start_time, *timeout;
		int	blocked = sslsock->s.is_blocked, has_timeout = 0;

#ifdef HAVE_TLS_SNI
		if (sslsock->is_client) {
			php_openssl_enable_client_sni(stream, sslsock);
		}
#endif

		if (!sslsock->state_set) {
			if (sslsock->is_client) {
				SSL_set_connect_state(sslsock->ssl_handle);
			} else {
				SSL_set_accept_state(sslsock->ssl_handle);
			}
			sslsock->state_set = 1;
		}

		if (SUCCESS == php_set_sock_blocking(sslsock->s.socket, 0)) {
			sslsock->s.is_blocked = 0;
			/* The following mode are added only if we are able to change socket
			 * to non blocking mode which is also used for read and write */
			SSL_set_mode(
				sslsock->ssl_handle,
				(
					SSL_get_mode(sslsock->ssl_handle) |
					SSL_MODE_ENABLE_PARTIAL_WRITE |
					SSL_MODE_ACCEPT_MOVING_WRITE_BUFFER
				)
			);
		}

		timeout = sslsock->is_client ? &sslsock->connect_timeout : &sslsock->s.timeout;
		has_timeout = !sslsock->s.is_blocked && (timeout->tv_sec || timeout->tv_usec);
		/* gettimeofday is not monotonic; using it here is not strictly correct */
		if (has_timeout) {
			gettimeofday(&start_time, NULL);
		}

		do {
			struct timeval cur_time, elapsed_time;

			ERR_clear_error();
			if (sslsock->is_client) {
				n = SSL_connect(sslsock->ssl_handle);
			} else {
				n = SSL_accept(sslsock->ssl_handle);
			}

			if (has_timeout) {
				gettimeofday(&cur_time, NULL);
				elapsed_time = php_openssl_subtract_timeval(cur_time, start_time);

				if (php_openssl_compare_timeval( elapsed_time, *timeout) > 0) {
					php_error_docref(NULL, E_WARNING, "SSL: Handshake timed out");
					return -1;
				}
			}

			if (n <= 0) {
				/* in case of SSL_ERROR_WANT_READ/WRITE, do not retry in non-blocking mode */
				retry = php_openssl_handle_ssl_error(stream, n, blocked);
				if (retry) {
					/* wait until something interesting happens in the socket. It may be a
					 * timeout. Also consider the unlikely of possibility of a write block  */
					int err = SSL_get_error(sslsock->ssl_handle, n);
					struct timeval left_time;

					if (has_timeout) {
						left_time = php_openssl_subtract_timeval(*timeout, elapsed_time);
					}
					php_pollfd_for(sslsock->s.socket, (err == SSL_ERROR_WANT_READ) ?
						(POLLIN|POLLPRI) : POLLOUT, has_timeout ? &left_time : NULL);
				}
			} else {
				retry = 0;
			}
		} while (retry);

		if (sslsock->s.is_blocked != blocked && SUCCESS == php_set_sock_blocking(sslsock->s.socket, blocked)) {
			sslsock->s.is_blocked = blocked;
		}

		if (n == 1) {
			peer_cert = SSL_get_peer_certificate(sslsock->ssl_handle);
			if (peer_cert && PHP_STREAM_CONTEXT(stream)) {
				cert_captured = php_openssl_capture_peer_certs(stream, sslsock, peer_cert);
			}

			if (FAILURE == php_openssl_apply_peer_verification_policy(sslsock->ssl_handle, peer_cert, stream)) {
				SSL_shutdown(sslsock->ssl_handle);
				n = -1;
			} else {
				sslsock->ssl_active = 1;

				if (PHP_STREAM_CONTEXT(stream)) {
					zval *val;
					if (NULL != (val = php_stream_context_get_option(PHP_STREAM_CONTEXT(stream),
						"ssl", "capture_session_meta"))
					) {
						 php_error(E_DEPRECATED,
							"capture_session_meta is deprecated; its information is now available via stream_get_meta_data()"
                        );
					}

					if (val && zend_is_true(val)) {
						zval meta_arr;
						ZVAL_ARR(&meta_arr, php_openssl_capture_session_meta(sslsock->ssl_handle));
						php_stream_context_set_option(PHP_STREAM_CONTEXT(stream), "ssl", "session_meta", &meta_arr);
						zval_ptr_dtor(&meta_arr);
					}
				}
			}
		} else if (errno == EAGAIN) {
			n = 0;
		} else {
			n = -1;
			/* We want to capture the peer cert even if verification fails*/
			peer_cert = SSL_get_peer_certificate(sslsock->ssl_handle);
			if (peer_cert && PHP_STREAM_CONTEXT(stream)) {
				cert_captured = php_openssl_capture_peer_certs(stream, sslsock, peer_cert);
			}
		}

		if (n && peer_cert && cert_captured == 0) {
			X509_free(peer_cert);
		}

		return n;

	} else if (!cparam->inputs.activate && sslsock->ssl_active) {
		/* deactivate - common for server/client */
		SSL_shutdown(sslsock->ssl_handle);
		sslsock->ssl_active = 0;
	}

	return -1;
}