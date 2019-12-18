#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_bool ;
struct TYPE_12__ {int /*<<< orphan*/  s; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ smart_str ;
struct TYPE_13__ {int eof; scalar_t__ abstract; } ;
typedef  TYPE_3__ php_stream ;
struct TYPE_11__ {int is_blocked; } ;
struct TYPE_14__ {int /*<<< orphan*/  ssl_handle; TYPE_1__ s; } ;
typedef  TYPE_4__ php_openssl_netstream_data_t ;
typedef  int /*<<< orphan*/  esbuf ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ERR_GET_REASON (unsigned long) ; 
 int /*<<< orphan*/  ERR_error_string_n (unsigned long,char*,int) ; 
 unsigned long ERR_get_error () ; 
 int /*<<< orphan*/  ERR_peek_error () ; 
 int /*<<< orphan*/  E_WARNING ; 
#define  SSL_ERROR_SYSCALL 132 
#define  SSL_ERROR_WANT_READ 131 
#define  SSL_ERROR_WANT_WRITE 130 
#define  SSL_ERROR_ZERO_RETURN 129 
 int SSL_RECEIVED_SHUTDOWN ; 
#define  SSL_R_NO_SHARED_CIPHER 128 
 int SSL_SENT_SHUTDOWN ; 
 int SSL_get_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SSL_set_shutdown (int /*<<< orphan*/ ,int) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  php_openssl_is_http_stream_talking_to_iis (TYPE_3__*) ; 
 int /*<<< orphan*/  php_socket_errno () ; 
 char* php_socket_strerror (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smart_str_0 (TYPE_2__*) ; 
 int /*<<< orphan*/  smart_str_appendc (TYPE_2__*,char) ; 
 int /*<<< orphan*/  smart_str_appends (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  smart_str_free (TYPE_2__*) ; 

__attribute__((used)) static int php_openssl_handle_ssl_error(php_stream *stream, int nr_bytes, zend_bool is_init) /* {{{ */
{
	php_openssl_netstream_data_t *sslsock = (php_openssl_netstream_data_t*)stream->abstract;
	int err = SSL_get_error(sslsock->ssl_handle, nr_bytes);
	char esbuf[512];
	smart_str ebuf = {0};
	unsigned long ecode;
	int retry = 1;

	switch(err) {
		case SSL_ERROR_ZERO_RETURN:
			/* SSL terminated (but socket may still be active) */
			retry = 0;
			break;
		case SSL_ERROR_WANT_READ:
		case SSL_ERROR_WANT_WRITE:
			/* re-negotiation, or perhaps the SSL layer needs more
			 * packets: retry in next iteration */
			errno = EAGAIN;
			retry = is_init ? 1 : sslsock->s.is_blocked;
			break;
		case SSL_ERROR_SYSCALL:
			if (ERR_peek_error() == 0) {
				if (nr_bytes == 0) {
					if (!php_openssl_is_http_stream_talking_to_iis(stream) && ERR_get_error() != 0) {
						php_error_docref(NULL, E_WARNING, "SSL: fatal protocol error");
					}
					SSL_set_shutdown(sslsock->ssl_handle, SSL_SENT_SHUTDOWN|SSL_RECEIVED_SHUTDOWN);
					stream->eof = 1;
					retry = 0;
				} else {
					char *estr = php_socket_strerror(php_socket_errno(), NULL, 0);

					php_error_docref(NULL, E_WARNING,
							"SSL: %s", estr);

					efree(estr);
					retry = 0;
				}
				break;
			}


			/* fall through */
		default:
			/* some other error */
			ecode = ERR_get_error();

			switch (ERR_GET_REASON(ecode)) {
				case SSL_R_NO_SHARED_CIPHER:
					php_error_docref(NULL, E_WARNING,
							"SSL_R_NO_SHARED_CIPHER: no suitable shared cipher could be used.  "
							"This could be because the server is missing an SSL certificate "
							"(local_cert context option)");
					retry = 0;
					break;

				default:
					do {
						/* NULL is automatically added */
						ERR_error_string_n(ecode, esbuf, sizeof(esbuf));
						if (ebuf.s) {
							smart_str_appendc(&ebuf, '\n');
						}
						smart_str_appends(&ebuf, esbuf);
					} while ((ecode = ERR_get_error()) != 0);

					smart_str_0(&ebuf);

					php_error_docref(NULL, E_WARNING,
							"SSL operation failed with code %d. %s%s",
							err,
							ebuf.s ? "OpenSSL Error messages:\n" : "",
							ebuf.s ? ZSTR_VAL(ebuf.s) : "");
					if (ebuf.s) {
						smart_str_free(&ebuf);
					}
			}

			retry = 0;
			errno = 0;
	}
	return retry;
}