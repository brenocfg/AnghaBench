#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_4__ {scalar_t__ log_error; int /*<<< orphan*/  tcp_nodelay; int /*<<< orphan*/  fd; int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_ERROR_IGNORE_EINVAL ; 
 scalar_t__ NGX_ERROR_INFO ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_CORE ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  NGX_TCP_NODELAY_SET ; 
 int /*<<< orphan*/  NGX_TCP_NODELAY_UNSET ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  ngx_connection_error (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_socket_errno ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int) ; 

ngx_int_t
ngx_tcp_nodelay(ngx_connection_t *c)
{
    int  tcp_nodelay;

    if (c->tcp_nodelay != NGX_TCP_NODELAY_UNSET) {
        return NGX_OK;
    }

    ngx_log_debug0(NGX_LOG_DEBUG_CORE, c->log, 0, "tcp_nodelay");

    tcp_nodelay = 1;

    if (setsockopt(c->fd, IPPROTO_TCP, TCP_NODELAY,
                   (const void *) &tcp_nodelay, sizeof(int))
        == -1)
    {
#if (NGX_SOLARIS)
        if (c->log_error == NGX_ERROR_INFO) {

            /* Solaris returns EINVAL if a socket has been shut down */
            c->log_error = NGX_ERROR_IGNORE_EINVAL;

            ngx_connection_error(c, ngx_socket_errno,
                                 "setsockopt(TCP_NODELAY) failed");

            c->log_error = NGX_ERROR_INFO;

            return NGX_ERROR;
        }
#endif

        ngx_connection_error(c, ngx_socket_errno,
                             "setsockopt(TCP_NODELAY) failed");
        return NGX_ERROR;
    }

    c->tcp_nodelay = NGX_TCP_NODELAY_SET;

    return NGX_OK;
}