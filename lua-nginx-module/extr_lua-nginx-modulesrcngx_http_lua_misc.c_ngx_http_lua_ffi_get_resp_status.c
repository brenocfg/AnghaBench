#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_socket_t ;
struct TYPE_6__ {int status; } ;
struct TYPE_7__ {int err_status; scalar_t__ http_version; TYPE_2__ headers_out; TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_5__ {scalar_t__ fd; } ;

/* Variables and functions */
 int NGX_HTTP_LUA_FFI_BAD_CONTEXT ; 
 scalar_t__ NGX_HTTP_VERSION_9 ; 

int
ngx_http_lua_ffi_get_resp_status(ngx_http_request_t *r)
{
    if (r->connection->fd == (ngx_socket_t) -1) {
        return NGX_HTTP_LUA_FFI_BAD_CONTEXT;
    }

    if (r->err_status) {
        return r->err_status;

    } else if (r->headers_out.status) {
        return r->headers_out.status;

    } else if (r->http_version == NGX_HTTP_VERSION_9) {
        return 9;

    } else {
        return 0;
    }
}