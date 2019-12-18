#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ abstract; } ;
typedef  TYPE_1__ php_stream ;
struct TYPE_5__ {int /*<<< orphan*/  socket; } ;
typedef  TYPE_2__ php_netstream_data_t ;

/* Variables and functions */
 int fsync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_sockop_flush(php_stream *stream)
{
#if 0
	php_netstream_data_t *sock = (php_netstream_data_t*)stream->abstract;
	return fsync(sock->socket);
#endif
	return 0;
}