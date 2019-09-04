#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ abstract; } ;
typedef  TYPE_2__ php_stream ;
struct TYPE_7__ {scalar_t__ socket; } ;
struct TYPE_9__ {unsigned int sni_cert_count; struct TYPE_9__* reneg; struct TYPE_9__* url_name; struct TYPE_9__* sni_certs; struct TYPE_9__* name; int /*<<< orphan*/ * ctx; TYPE_1__ s; int /*<<< orphan*/ * ssl_handle; scalar_t__ ssl_active; } ;
typedef  TYPE_3__ php_openssl_netstream_data_t ;

/* Variables and functions */
 scalar_t__ SOCK_ERR ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 int /*<<< orphan*/  pefree (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_stream_is_persistent (TYPE_2__*) ; 

__attribute__((used)) static int php_openssl_sockop_close(php_stream *stream, int close_handle) /* {{{ */
{
	php_openssl_netstream_data_t *sslsock = (php_openssl_netstream_data_t*)stream->abstract;
#ifdef PHP_WIN32
	int n;
#endif
	unsigned i;

	if (close_handle) {
		if (sslsock->ssl_active) {
			SSL_shutdown(sslsock->ssl_handle);
			sslsock->ssl_active = 0;
		}
		if (sslsock->ssl_handle) {
			SSL_free(sslsock->ssl_handle);
			sslsock->ssl_handle = NULL;
		}
		if (sslsock->ctx) {
			SSL_CTX_free(sslsock->ctx);
			sslsock->ctx = NULL;
		}
#ifdef HAVE_TLS_ALPN
		if (sslsock->alpn_ctx.data) {
			pefree(sslsock->alpn_ctx.data, php_stream_is_persistent(stream));
		}
#endif
#ifdef PHP_WIN32
		if (sslsock->s.socket == -1)
			sslsock->s.socket = SOCK_ERR;
#endif
		if (sslsock->s.socket != SOCK_ERR) {
#ifdef PHP_WIN32
			/* prevent more data from coming in */
			shutdown(sslsock->s.socket, SHUT_RD);

			/* try to make sure that the OS sends all data before we close the connection.
			 * Essentially, we are waiting for the socket to become writeable, which means
			 * that all pending data has been sent.
			 * We use a small timeout which should encourage the OS to send the data,
			 * but at the same time avoid hanging indefinitely.
			 * */
			do {
				n = php_pollfd_for_ms(sslsock->s.socket, POLLOUT, 500);
			} while (n == -1 && php_socket_errno() == EINTR);
#endif
			closesocket(sslsock->s.socket);
			sslsock->s.socket = SOCK_ERR;
		}
	}

	if (sslsock->sni_certs) {
		for (i = 0; i < sslsock->sni_cert_count; i++) {
			if (sslsock->sni_certs[i].ctx) {
				SSL_CTX_free(sslsock->sni_certs[i].ctx);
				pefree(sslsock->sni_certs[i].name, php_stream_is_persistent(stream));
			}
		}
		pefree(sslsock->sni_certs, php_stream_is_persistent(stream));
		sslsock->sni_certs = NULL;
	}

	if (sslsock->url_name) {
		pefree(sslsock->url_name, php_stream_is_persistent(stream));
	}

	if (sslsock->reneg) {
		pefree(sslsock->reneg, php_stream_is_persistent(stream));
	}

	pefree(sslsock, php_stream_is_persistent(stream));

	return 0;
}