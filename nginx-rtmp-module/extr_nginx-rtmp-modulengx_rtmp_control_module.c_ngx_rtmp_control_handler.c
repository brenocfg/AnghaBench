#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  int ngx_uint_t ;
struct TYPE_24__ {char* data; int len; } ;
typedef  TYPE_3__ ngx_str_t ;
struct TYPE_25__ {int control; } ;
typedef  TYPE_4__ ngx_rtmp_control_loc_conf_t ;
struct TYPE_26__ {TYPE_3__ method; int /*<<< orphan*/  sessions; } ;
typedef  TYPE_5__ ngx_rtmp_control_ctx_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_22__ {int len; char* data; } ;
struct TYPE_27__ {int /*<<< orphan*/  pool; TYPE_2__* connection; TYPE_1__ uri; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_23__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 scalar_t__ NGX_OK ; 
 int NGX_RTMP_CONTROL_DROP ; 
 int NGX_RTMP_CONTROL_RECORD ; 
 int NGX_RTMP_CONTROL_REDIRECT ; 
 scalar_t__ ngx_array_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 TYPE_4__* ngx_http_get_module_loc_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_3__*,TYPE_3__*) ; 
 TYPE_5__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_rtmp_control_drop (TYPE_6__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_rtmp_control_module ; 
 int /*<<< orphan*/  ngx_rtmp_control_record (TYPE_6__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_rtmp_control_redirect (TYPE_6__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_str_null (TYPE_3__*) ; 
 scalar_t__ ngx_strncmp (char*,char*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_control_handler(ngx_http_request_t *r)
{
    u_char                       *p;
    ngx_str_t                     section, method;
    ngx_uint_t                    n;
    ngx_rtmp_control_ctx_t       *ctx;
    ngx_rtmp_control_loc_conf_t  *llcf;

    llcf = ngx_http_get_module_loc_conf(r, ngx_rtmp_control_module);
    if (llcf->control == 0) {
        return NGX_DECLINED;
    }

    /* uri format: .../section/method?args */

    ngx_str_null(&section);
    ngx_str_null(&method);

    for (n = r->uri.len; n; --n) {
        p = &r->uri.data[n - 1];

        if (*p != '/') {
            continue;
        }

        if (method.data) {
            section.data = p + 1;
            section.len  = method.data - section.data - 1;
            break;
        }

        method.data = p + 1;
        method.len  = r->uri.data + r->uri.len - method.data;
    }

    ngx_log_debug2(NGX_LOG_DEBUG_RTMP, r->connection->log, 0,
                   "rtmp_control: section='%V' method='%V'",
                   &section, &method);

    ctx = ngx_pcalloc(r->pool, sizeof(ngx_rtmp_control_ctx_t));
    if (ctx == NULL) {
        return NGX_ERROR;
    }

    ngx_http_set_ctx(r, ctx, ngx_rtmp_control_module);

    if (ngx_array_init(&ctx->sessions, r->pool, 1, sizeof(void *)) != NGX_OK) {
        return NGX_ERROR;
    }

    ctx->method = method;

#define NGX_RTMP_CONTROL_SECTION(flag, secname)                             \
    if (llcf->control & NGX_RTMP_CONTROL_##flag &&                          \
        section.len == sizeof(#secname) - 1 &&                              \
        ngx_strncmp(section.data, #secname, sizeof(#secname) - 1) == 0)     \
    {                                                                       \
        return ngx_rtmp_control_##secname(r, &method);                      \
    }

    NGX_RTMP_CONTROL_SECTION(RECORD, record);
    NGX_RTMP_CONTROL_SECTION(DROP, drop);
    NGX_RTMP_CONTROL_SECTION(REDIRECT, redirect);

#undef NGX_RTMP_CONTROL_SECTION

    return NGX_DECLINED;
}