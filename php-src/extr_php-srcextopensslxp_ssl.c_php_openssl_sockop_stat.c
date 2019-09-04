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
typedef  int /*<<< orphan*/  php_stream_statbuf ;
typedef  int /*<<< orphan*/  php_stream ;
struct TYPE_2__ {int (* stat ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__ php_stream_socket_ops ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int php_openssl_sockop_stat(php_stream *stream, php_stream_statbuf *ssb) /* {{{ */
{
	return php_stream_socket_ops.stat(stream, ssb);
}