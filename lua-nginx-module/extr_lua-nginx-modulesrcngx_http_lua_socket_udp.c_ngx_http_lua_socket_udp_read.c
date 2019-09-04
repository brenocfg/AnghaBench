#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_12__ {TYPE_4__* connection; } ;
struct TYPE_13__ {int /*<<< orphan*/  read_timeout; int /*<<< orphan*/  socket_errno; scalar_t__ received; int /*<<< orphan*/  recv_buf_size; TYPE_1__ udp_connection; scalar_t__ waiting; } ;
typedef  TYPE_2__ ngx_http_lua_socket_udp_upstream_t ;
struct TYPE_14__ {scalar_t__ timer_set; scalar_t__ active; } ;
typedef  TYPE_3__ ngx_event_t ;
struct TYPE_15__ {int /*<<< orphan*/  log; TYPE_3__* read; } ;
typedef  TYPE_4__ ngx_connection_t ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_SOCKET_FT_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_del_timer (TYPE_3__*) ; 
 scalar_t__ ngx_handle_read_event (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_udp_buffer ; 
 int /*<<< orphan*/  ngx_http_lua_socket_udp_handle_error (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_udp_handle_success (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_socket_errno ; 
 scalar_t__ ngx_udp_recv (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_socket_udp_read(ngx_http_request_t *r,
    ngx_http_lua_socket_udp_upstream_t *u)
{
    ngx_connection_t            *c;
    ngx_event_t                 *rev;
    ssize_t                      n;

    c = u->udp_connection.connection;
    rev = c->read;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "lua udp socket read data: waiting: %d", (int) u->waiting);

    n = ngx_udp_recv(u->udp_connection.connection,
                     ngx_http_lua_socket_udp_buffer, u->recv_buf_size);

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "lua udp recv returned %z", n);

    if (n >= 0) {
        u->received = n;
        ngx_http_lua_socket_udp_handle_success(r, u);
        return NGX_OK;
    }

    if (n == NGX_ERROR) {
        u->socket_errno = ngx_socket_errno;
        ngx_http_lua_socket_udp_handle_error(r, u,
                                             NGX_HTTP_LUA_SOCKET_FT_ERROR);
        return NGX_ERROR;
    }

    /* n == NGX_AGAIN */

#if 1
    if (ngx_handle_read_event(rev, 0) != NGX_OK) {
        ngx_http_lua_socket_udp_handle_error(r, u,
                                             NGX_HTTP_LUA_SOCKET_FT_ERROR);
        return NGX_ERROR;
    }
#endif

    if (rev->active) {
        ngx_add_timer(rev, u->read_timeout);

    } else if (rev->timer_set) {
        ngx_del_timer(rev);
    }

    return NGX_AGAIN;
}