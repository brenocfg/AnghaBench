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
struct TYPE_6__ {int /*<<< orphan*/  sb; } ;
typedef  TYPE_1__ php_stream_statbuf ;
struct TYPE_7__ {scalar_t__ abstract; } ;
typedef  TYPE_2__ php_stream ;
struct TYPE_8__ {int /*<<< orphan*/  socket; } ;
typedef  TYPE_3__ php_netstream_data_t ;

/* Variables and functions */
 int zend_fstat (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int php_sockop_stat(php_stream *stream, php_stream_statbuf *ssb)
{
#if ZEND_WIN32
	return 0;
#else
	php_netstream_data_t *sock = (php_netstream_data_t*)stream->abstract;

	return zend_fstat(sock->socket, &ssb->sb);
#endif
}