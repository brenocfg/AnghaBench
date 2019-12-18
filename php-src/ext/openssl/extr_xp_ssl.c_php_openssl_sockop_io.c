#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  stream_shutdown_t ;
typedef  int ssize_t ;
struct TYPE_14__ {int eof; scalar_t__ abstract; } ;
typedef  TYPE_3__ php_stream ;
struct TYPE_13__ {int is_blocked; int timeout_event; int /*<<< orphan*/  socket; struct timeval timeout; } ;
struct TYPE_15__ {TYPE_2__ s; int /*<<< orphan*/  ssl_handle; TYPE_1__* reneg; scalar_t__ ssl_active; } ;
typedef  TYPE_4__ php_openssl_netstream_data_t ;
struct TYPE_16__ {size_t (* read ) (TYPE_3__*,char*,size_t) ;size_t (* write ) (TYPE_3__*,char*,size_t) ;} ;
struct TYPE_12__ {scalar_t__ should_close; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 size_t INT_MAX ; 
 int /*<<< orphan*/  PHP_STREAM_CONTEXT (TYPE_3__*) ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLPRI ; 
 scalar_t__ SHUT_RDWR ; 
 int SSL_ERROR_NONE ; 
 int SSL_ERROR_WANT_READ ; 
 int SSL_ERROR_WANT_WRITE ; 
 int SSL_get_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SSL_pending (int /*<<< orphan*/ ) ; 
 int SSL_read (int /*<<< orphan*/ ,char*,int) ; 
 int SSL_write (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 scalar_t__ php_openssl_compare_timeval (struct timeval,struct timeval) ; 
 int php_openssl_handle_ssl_error (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 struct timeval php_openssl_subtract_timeval (struct timeval,struct timeval) ; 
 int /*<<< orphan*/  php_pollfd_for (int /*<<< orphan*/ ,int,struct timeval*) ; 
 scalar_t__ php_set_sock_blocking (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  php_stream_notify_progress_increment (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_8__ php_stream_socket_ops ; 
 int /*<<< orphan*/  php_stream_xport_shutdown (TYPE_3__*,int /*<<< orphan*/ ) ; 
 size_t stub1 (TYPE_3__*,char*,size_t) ; 
 size_t stub2 (TYPE_3__*,char*,size_t) ; 

__attribute__((used)) static ssize_t php_openssl_sockop_io(int read, php_stream *stream, char *buf, size_t count) /* {{{ */
{
	php_openssl_netstream_data_t *sslsock = (php_openssl_netstream_data_t*)stream->abstract;

	/* Only do this if SSL is active. */
	if (sslsock->ssl_active) {
		int retry = 1;
		struct timeval start_time;
		struct timeval *timeout = NULL;
		int began_blocked = sslsock->s.is_blocked;
		int has_timeout = 0;
		int nr_bytes = 0;

		/* prevent overflow in openssl */
		if (count > INT_MAX) {
			count = INT_MAX;
		}

		/* never use a timeout with non-blocking sockets */
		if (began_blocked) {
			timeout = &sslsock->s.timeout;
		}

		if (timeout && php_set_sock_blocking(sslsock->s.socket, 0) == SUCCESS) {
			sslsock->s.is_blocked = 0;
		}

		if (!sslsock->s.is_blocked && timeout && (timeout->tv_sec || timeout->tv_usec)) {
			has_timeout = 1;
			/* gettimeofday is not monotonic; using it here is not strictly correct */
			gettimeofday(&start_time, NULL);
		}

		/* Main IO loop. */
		do {
			struct timeval cur_time, elapsed_time, left_time;

			/* If we have a timeout to check, figure out how much time has elapsed since we started. */
			if (has_timeout) {
				gettimeofday(&cur_time, NULL);

				/* Determine how much time we've taken so far. */
				elapsed_time = php_openssl_subtract_timeval(cur_time, start_time);

				/* and return an error if we've taken too long. */
				if (php_openssl_compare_timeval(elapsed_time, *timeout) > 0 ) {
					/* If the socket was originally blocking, set it back. */
					if (began_blocked) {
						php_set_sock_blocking(sslsock->s.socket, 1);
						sslsock->s.is_blocked = 1;
					}
					sslsock->s.timeout_event = 1;
					return -1;
				}
			}

			/* Now, do the IO operation. Don't block if we can't complete... */
			ERR_clear_error();
			if (read) {
				nr_bytes = SSL_read(sslsock->ssl_handle, buf, (int)count);

				if (sslsock->reneg && sslsock->reneg->should_close) {
					/* renegotiation rate limiting triggered */
					php_stream_xport_shutdown(stream, (stream_shutdown_t)SHUT_RDWR);
					nr_bytes = 0;
					stream->eof = 1;
					 break;
				}
			} else {
				nr_bytes = SSL_write(sslsock->ssl_handle, buf, (int)count);
			}

			/* Now, how much time until we time out? */
			if (has_timeout) {
				left_time = php_openssl_subtract_timeval( *timeout, elapsed_time );
			}

			/* If we didn't do anything on the last loop (or an error) check to see if we should retry or exit. */
			if (nr_bytes <= 0) {

				/* Get the error code from SSL, and check to see if it's an error or not. */
				int err = SSL_get_error(sslsock->ssl_handle, nr_bytes );
				retry = php_openssl_handle_ssl_error(stream, nr_bytes, 0);

				/* If we get this (the above doesn't check) then we'll retry as well. */
				if (errno == EAGAIN && err == SSL_ERROR_WANT_READ && read) {
					retry = 1;
				}
				if (errno == EAGAIN && err == SSL_ERROR_WANT_WRITE && read == 0) {
					retry = 1;
				}

				/* Also, on reads, we may get this condition on an EOF. We should check properly. */
				if (read) {
					stream->eof = (retry == 0 && errno != EAGAIN && !SSL_pending(sslsock->ssl_handle));
				}

				/* Don't loop indefinitely in non-blocking mode if no data is available */
				if (began_blocked == 0) {
					break;
				}

				/* Now, if we have to wait some time, and we're supposed to be blocking, wait for the socket to become
				 * available. Now, php_pollfd_for uses select to wait up to our time_left value only...
				 */
				if (retry) {
					if (read) {
						php_pollfd_for(sslsock->s.socket, (err == SSL_ERROR_WANT_WRITE) ?
							(POLLOUT|POLLPRI) : (POLLIN|POLLPRI), has_timeout ? &left_time : NULL);
					} else {
						php_pollfd_for(sslsock->s.socket, (err == SSL_ERROR_WANT_READ) ?
							(POLLIN|POLLPRI) : (POLLOUT|POLLPRI), has_timeout ? &left_time : NULL);
					}
				}
			} else {
				/* Else, if we got bytes back, check for possible errors. */
				int err = SSL_get_error(sslsock->ssl_handle, nr_bytes);

				/* If we didn't get any error, then let's return it to PHP. */
				if (err == SSL_ERROR_NONE) {
					break;
				}

				/* Otherwise, we need to wait again (up to time_left or we get an error) */
				if (began_blocked) {
					if (read) {
						php_pollfd_for(sslsock->s.socket, (err == SSL_ERROR_WANT_WRITE) ?
							(POLLOUT|POLLPRI) : (POLLIN|POLLPRI), has_timeout ? &left_time : NULL);
					} else {
						php_pollfd_for(sslsock->s.socket, (err == SSL_ERROR_WANT_READ) ?
							(POLLIN|POLLPRI) : (POLLOUT|POLLPRI), has_timeout ? &left_time : NULL);
					}
				}
			}

			/* Finally, we keep going until we got data, and an SSL_ERROR_NONE, unless we had an error. */
		} while (retry);

		/* Tell PHP if we read / wrote bytes. */
		if (nr_bytes > 0) {
			php_stream_notify_progress_increment(PHP_STREAM_CONTEXT(stream), nr_bytes, 0);
		}

		/* And if we were originally supposed to be blocking, let's reset the socket to that. */
		if (began_blocked && php_set_sock_blocking(sslsock->s.socket, 1) == SUCCESS) {
			sslsock->s.is_blocked = 1;
		}

		return 0 > nr_bytes ? 0 : nr_bytes;
	} else {
		size_t nr_bytes = 0;

		/* This block is if we had no timeout... We will just sit and wait forever on the IO operation. */
		if (read) {
			nr_bytes = php_stream_socket_ops.read(stream, buf, count);
		} else {
			nr_bytes = php_stream_socket_ops.write(stream, buf, count);
		}

		return nr_bytes;
	}
}