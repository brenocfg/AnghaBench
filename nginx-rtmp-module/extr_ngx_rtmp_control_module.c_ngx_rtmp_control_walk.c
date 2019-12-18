#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_11__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_core_srv_conf_t ;
struct TYPE_9__ {scalar_t__ nelts; int /*<<< orphan*/ ** elts; } ;
struct TYPE_12__ {TYPE_1__ servers; } ;
typedef  TYPE_4__ ngx_rtmp_core_main_conf_t ;
typedef  char* (* ngx_rtmp_control_handler_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
struct TYPE_10__ {scalar_t__ nelts; int /*<<< orphan*/ ** elts; } ;
struct TYPE_13__ {TYPE_2__ sessions; } ;
typedef  TYPE_5__ ngx_rtmp_control_ctx_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;

/* Variables and functions */
 char const* NGX_CONF_OK ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_atoi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_3__*) ; 
 TYPE_5__* ngx_http_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_control_module ; 
 char* ngx_rtmp_control_walk_server (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* ngx_rtmp_core_main_conf ; 

__attribute__((used)) static const char *
ngx_rtmp_control_walk(ngx_http_request_t *r, ngx_rtmp_control_handler_t h)
{
    ngx_rtmp_core_main_conf_t  *cmcf = ngx_rtmp_core_main_conf;

    ngx_str_t                   srv;
    ngx_uint_t                  sn, n;
    const char                 *msg;
    ngx_rtmp_session_t        **s;
    ngx_rtmp_control_ctx_t     *ctx;
    ngx_rtmp_core_srv_conf_t  **pcscf;

    sn = 0;
    if (ngx_http_arg(r, (u_char *) "srv", sizeof("srv") - 1, &srv) == NGX_OK) {
        sn = ngx_atoi(srv.data, srv.len);
    }

    if (sn >= cmcf->servers.nelts) {
        return "Server index out of range";
    }

    pcscf  = cmcf->servers.elts;
    pcscf += sn;

    msg = ngx_rtmp_control_walk_server(r, *pcscf);
    if (msg != NGX_CONF_OK) {
        return msg;
    }

    ctx = ngx_http_get_module_ctx(r, ngx_rtmp_control_module);

    s = ctx->sessions.elts;
    for (n = 0; n < ctx->sessions.nelts; n++) {
        msg = h(r, s[n]);
        if (msg != NGX_CONF_OK) {
            return msg;
        }
    }

    return NGX_CONF_OK;
}