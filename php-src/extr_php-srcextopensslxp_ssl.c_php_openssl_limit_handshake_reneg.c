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
typedef  int /*<<< orphan*/  zval ;
typedef  int zend_long ;
struct timeval {int tv_sec; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; scalar_t__ abstract; } ;
typedef  TYPE_2__ php_stream ;
struct TYPE_9__ {TYPE_1__* reneg; } ;
typedef  TYPE_3__ php_openssl_netstream_data_t ;
struct TYPE_7__ {scalar_t__ prev_handshake; int tokens; int limit; int window; int should_close; } ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ FAILURE ; 
 scalar_t__ IS_TRUE ; 
 scalar_t__ PHP_STREAM_CONTEXT (TYPE_2__*) ; 
 int /*<<< orphan*/  PHP_STREAM_FLAG_NO_FCLOSE ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ call_user_function_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* php_openssl_get_stream_from_ssl_handle (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * php_stream_context_get_option (scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  php_stream_to_zval (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_openssl_limit_handshake_reneg(const SSL *ssl) /* {{{ */
{
	php_stream *stream;
	php_openssl_netstream_data_t *sslsock;
	struct timeval now;
	zend_long elapsed_time;

	stream = php_openssl_get_stream_from_ssl_handle(ssl);
	sslsock = (php_openssl_netstream_data_t*)stream->abstract;
	gettimeofday(&now, NULL);

	/* The initial handshake is never rate-limited */
	if (sslsock->reneg->prev_handshake == 0) {
		sslsock->reneg->prev_handshake = now.tv_sec;
		return;
	}

	elapsed_time = (now.tv_sec - sslsock->reneg->prev_handshake);
	sslsock->reneg->prev_handshake = now.tv_sec;
	sslsock->reneg->tokens -= (elapsed_time * (sslsock->reneg->limit / sslsock->reneg->window));

	if (sslsock->reneg->tokens < 0) {
		sslsock->reneg->tokens = 0;
	}
	++sslsock->reneg->tokens;

	/* The token level exceeds our allowed limit */
	if (sslsock->reneg->tokens > sslsock->reneg->limit) {
		zval *val;


		sslsock->reneg->should_close = 1;

		if (PHP_STREAM_CONTEXT(stream) && (val = php_stream_context_get_option(PHP_STREAM_CONTEXT(stream),
				"ssl", "reneg_limit_callback")) != NULL
		) {
			zval param, retval;

			php_stream_to_zval(stream, &param);

			/* Closing the stream inside this callback would segfault! */
			stream->flags |= PHP_STREAM_FLAG_NO_FCLOSE;
			if (FAILURE == call_user_function_ex(NULL, NULL, val, &retval, 1, &param, 0, NULL)) {
				php_error(E_WARNING, "SSL: failed invoking reneg limit notification callback");
			}
			stream->flags ^= PHP_STREAM_FLAG_NO_FCLOSE;

			/* If the reneg_limit_callback returned true don't auto-close */
			if (Z_TYPE(retval) == IS_TRUE) {
				sslsock->reneg->should_close = 0;
			}

			zval_ptr_dtor(&retval);
		} else {
			php_error_docref(NULL, E_WARNING,
				"SSL: client-initiated handshake rate limit exceeded by peer");
		}
	}
}