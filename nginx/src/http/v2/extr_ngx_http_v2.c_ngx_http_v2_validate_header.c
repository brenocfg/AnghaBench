#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_12__ {size_t len; char* data; } ;
struct TYPE_16__ {char* data; size_t len; } ;
struct TYPE_13__ {TYPE_2__ value; TYPE_6__ name; } ;
typedef  TYPE_3__ ngx_http_v2_header_t ;
struct TYPE_14__ {int invalid_header; TYPE_1__* connection; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_15__ {scalar_t__ underscores_in_headers; } ;
typedef  TYPE_5__ ngx_http_core_srv_conf_t ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 char CR ; 
 char LF ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_5__* ngx_http_get_module_srv_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_6__*,...) ; 

__attribute__((used)) static ngx_int_t
ngx_http_v2_validate_header(ngx_http_request_t *r, ngx_http_v2_header_t *header)
{
    u_char                     ch;
    ngx_uint_t                 i;
    ngx_http_core_srv_conf_t  *cscf;

    r->invalid_header = 0;

    cscf = ngx_http_get_module_srv_conf(r, ngx_http_core_module);

    for (i = (header->name.data[0] == ':'); i != header->name.len; i++) {
        ch = header->name.data[i];

        if ((ch >= 'a' && ch <= 'z')
            || (ch == '-')
            || (ch >= '0' && ch <= '9')
            || (ch == '_' && cscf->underscores_in_headers))
        {
            continue;
        }

        if (ch == '\0' || ch == LF || ch == CR || ch == ':'
            || (ch >= 'A' && ch <= 'Z'))
        {
            ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                          "client sent invalid header name: \"%V\"",
                          &header->name);

            return NGX_ERROR;
        }

        r->invalid_header = 1;
    }

    for (i = 0; i != header->value.len; i++) {
        ch = header->value.data[i];

        if (ch == '\0' || ch == LF || ch == CR) {
            ngx_log_error(NGX_LOG_INFO, r->connection->log, 0,
                          "client sent header \"%V\" with "
                          "invalid value: \"%V\"",
                          &header->name, &header->value);

            return NGX_ERROR;
        }
    }

    return NGX_OK;
}