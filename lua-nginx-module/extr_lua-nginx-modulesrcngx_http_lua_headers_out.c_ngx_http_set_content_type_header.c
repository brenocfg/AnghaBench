#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_12__ {size_t len; char* data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_11__ {size_t content_type_len; int /*<<< orphan*/ * content_type_lowcase; int /*<<< orphan*/  content_type_hash; TYPE_2__ content_type; } ;
struct TYPE_13__ {TYPE_1__ headers_out; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_14__ {int /*<<< orphan*/  hash; } ;
typedef  TYPE_4__ ngx_http_lua_header_val_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_http_set_header_helper (TYPE_3__*,TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_set_content_type_header(ngx_http_request_t *r,
    ngx_http_lua_header_val_t *hv, ngx_str_t *value)
{
    ngx_uint_t          i;

    r->headers_out.content_type_len = value->len;

#if 1
    for (i = 0; i < value->len; i++) {
        if (value->data[i] == ';') {
            r->headers_out.content_type_len = i;
            break;
        }
    }
#endif

    r->headers_out.content_type = *value;
    r->headers_out.content_type_hash = hv->hash;
    r->headers_out.content_type_lowcase = NULL;

    value->len = 0;

    return ngx_http_set_header_helper(r, hv, value, NULL, 1);
}