#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_10__ {scalar_t__ last_modified_time; } ;
struct TYPE_12__ {TYPE_1__ headers_out; } ;
typedef  TYPE_3__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_header_val_t ;

/* Variables and functions */
 int /*<<< orphan*/  dd (char*,int) ; 
 int /*<<< orphan*/  ngx_http_clear_last_modified_header (TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ ngx_http_parse_time (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_set_builtin_header (TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static ngx_int_t ngx_http_set_last_modified_header(ngx_http_request_t *r,
    ngx_http_lua_header_val_t *hv, ngx_str_t *value)
{
    if (value->len == 0) {
        return ngx_http_clear_last_modified_header(r, hv, value);
    }

    r->headers_out.last_modified_time = ngx_http_parse_time(value->data,
                                                            value->len);

    dd("last modified time: %d", (int) r->headers_out.last_modified_time);

    return ngx_http_set_builtin_header(r, hv, value);
}