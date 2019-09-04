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
typedef  scalar_t__ ngx_socket_t ;
struct TYPE_5__ {struct TYPE_5__* main; TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
struct TYPE_4__ {scalar_t__ fd; } ;

/* Variables and functions */
 int NGX_HTTP_LUA_FFI_BAD_CONTEXT ; 

int
ngx_http_lua_ffi_is_subrequest(ngx_http_request_t *r)
{
    if (r->connection->fd == (ngx_socket_t) -1) {
        return NGX_HTTP_LUA_FFI_BAD_CONTEXT;
    }

    return r != r->main;
}