#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  ser_context ;
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_2__ {int bsd_socket; } ;
typedef  TYPE_1__ php_socket ;

/* Variables and functions */
 scalar_t__ FAILURE ; 
 scalar_t__ IS_RESOURCE ; 
 int /*<<< orphan*/  PHP_STREAM_AS_FD ; 
 int /*<<< orphan*/  REPORT_ERRORS ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_from_zval_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  php_file_le_pstream () ; 
 int /*<<< orphan*/  php_file_le_stream () ; 
 int /*<<< orphan*/  php_sockets_le_socket () ; 
 scalar_t__ php_stream_cast (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 scalar_t__ zend_fetch_resource2_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zend_fetch_resource_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void from_zval_write_fd_array_aux(zval *elem, unsigned i, void **args, ser_context *ctx)
{
	int *iarr = args[0];

	if (Z_TYPE_P(elem) == IS_RESOURCE) {
		php_stream *stream;
		php_socket *sock;

		sock = (php_socket *)zend_fetch_resource_ex(elem, NULL, php_sockets_le_socket());
		if (sock) {
			iarr[i] = sock->bsd_socket;
			return;
		}

		stream = (php_stream *)zend_fetch_resource2_ex(elem, NULL, php_file_le_stream(), php_file_le_pstream());
		if (stream == NULL) {
			do_from_zval_err(ctx, "resource is not a stream or a socket");
			return;
		}

		if (php_stream_cast(stream, PHP_STREAM_AS_FD, (void **)&iarr[i - 1],
				REPORT_ERRORS) == FAILURE) {
			do_from_zval_err(ctx, "cast stream to file descriptor failed");
			return;
		}
	} else {
		do_from_zval_err(ctx, "expected a resource variable");
	}
}