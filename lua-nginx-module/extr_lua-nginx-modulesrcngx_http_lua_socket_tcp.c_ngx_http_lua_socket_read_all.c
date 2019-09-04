#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_6__ {TYPE_2__* request; int /*<<< orphan*/  buf_in; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_3__ ngx_http_lua_socket_tcp_upstream_t ;
struct TYPE_5__ {TYPE_1__* connection; } ;
struct TYPE_4__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_http_lua_read_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_socket_read_all(void *data, ssize_t bytes)
{
    ngx_http_lua_socket_tcp_upstream_t      *u = data;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, u->request->connection->log, 0,
                   "lua tcp socket read all");
    return ngx_http_lua_read_all(&u->buffer, u->buf_in, bytes,
                                 u->request->connection->log);
}