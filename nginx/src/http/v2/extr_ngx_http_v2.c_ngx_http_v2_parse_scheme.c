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
typedef  int u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_7__ {scalar_t__ len; int* data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_8__ {TYPE_2__ schema; TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_6__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static ngx_int_t
ngx_http_v2_parse_scheme(ngx_http_request_t *r, ngx_str_t *value)
{
    u_char      c, ch;
    ngx_uint_t  i;

    if (r->schema.len) {
        ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                      "client sent duplicate :scheme header");

        return NGX_DECLINED;
    }

    if (value->len == 0) {
        ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                      "client sent empty :scheme header");

        return NGX_DECLINED;
    }

    for (i = 0; i < value->len; i++) {
        ch = value->data[i];

        c = (u_char) (ch | 0x20);
        if (c >= 'a' && c <= 'z') {
            continue;
        }

        if (((ch >= '0' && ch <= '9') || ch == '+' || ch == '-' || ch == '.')
            && i > 0)
        {
            continue;
        }

        ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                      "client sent invalid :scheme header: \"%V\"", value);

        return NGX_DECLINED;
    }

    r->schema = *value;

    return NGX_OK;
}