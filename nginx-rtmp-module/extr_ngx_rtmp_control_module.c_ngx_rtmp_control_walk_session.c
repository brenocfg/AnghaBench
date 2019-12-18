#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_11__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_12__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_13__ {int /*<<< orphan*/  publishing; TYPE_3__* session; } ;
typedef  TYPE_4__ ngx_rtmp_live_ctx_t ;
struct TYPE_14__ {int filter; int /*<<< orphan*/  sessions; } ;
typedef  TYPE_5__ ngx_rtmp_control_ctx_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_10__ {scalar_t__ number; TYPE_2__ addr_text; } ;

/* Variables and functions */
 char const* NGX_CONF_OK ; 
 scalar_t__ NGX_OK ; 
#define  NGX_RTMP_CONTROL_FILTER_CLIENT 130 
#define  NGX_RTMP_CONTROL_FILTER_PUBLISHER 129 
#define  NGX_RTMP_CONTROL_FILTER_SUBSCRIBER 128 
 TYPE_3__** ngx_array_push (int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_atoi (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ngx_http_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 TYPE_5__* ngx_http_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_control_module ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static const char *
ngx_rtmp_control_walk_session(ngx_http_request_t *r,
    ngx_rtmp_live_ctx_t *lctx)
{
    ngx_str_t                addr, *paddr, clientid;
    ngx_rtmp_session_t      *s, **ss;
    ngx_rtmp_control_ctx_t  *ctx;

    s = lctx->session;

    if (s == NULL || s->connection == NULL) {
        return NGX_CONF_OK;
    }

    if (ngx_http_arg(r, (u_char *) "addr", sizeof("addr") - 1, &addr)
        == NGX_OK)
    {
        paddr = &s->connection->addr_text;
        if (paddr->len != addr.len ||
            ngx_strncmp(paddr->data, addr.data, addr.len))
        {
            return NGX_CONF_OK;
        }
    }

    if (ngx_http_arg(r, (u_char *) "clientid", sizeof("clientid") - 1,
                     &clientid)
        == NGX_OK)
    {
        if (s->connection->number !=
            (ngx_uint_t) ngx_atoi(clientid.data, clientid.len))
        {
            return NGX_CONF_OK;
        }
    }

    ctx = ngx_http_get_module_ctx(r, ngx_rtmp_control_module);

    switch (ctx->filter) {
        case NGX_RTMP_CONTROL_FILTER_PUBLISHER:
            if (!lctx->publishing) {
                return NGX_CONF_OK;
            }
            break;

        case NGX_RTMP_CONTROL_FILTER_SUBSCRIBER:
            if (lctx->publishing) {
                return NGX_CONF_OK;
            }
            break;

        case NGX_RTMP_CONTROL_FILTER_CLIENT:
            break;
    }

    ss = ngx_array_push(&ctx->sessions);
    if (ss == NULL) {
        return "allocation error";
    }

    *ss = s;

    return NGX_CONF_OK;
}