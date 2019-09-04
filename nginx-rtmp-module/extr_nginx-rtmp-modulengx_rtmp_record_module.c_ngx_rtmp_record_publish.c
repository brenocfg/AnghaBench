#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
struct TYPE_19__ {TYPE_1__* connection; scalar_t__ auto_pushed; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_20__ {char* name; char* args; } ;
typedef  TYPE_4__ ngx_rtmp_record_ctx_t ;
struct TYPE_18__ {scalar_t__ nelts; } ;
struct TYPE_21__ {TYPE_2__ rec; } ;
typedef  TYPE_5__ ngx_rtmp_record_app_conf_t ;
struct TYPE_22__ {int /*<<< orphan*/  args; int /*<<< orphan*/  name; } ;
typedef  TYPE_6__ ngx_rtmp_publish_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_17__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  next_publish (TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_memcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_path_separator (char) ; 
 TYPE_5__* ngx_rtmp_get_module_app_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_rtmp_get_module_ctx (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_rtmp_record_init (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_rtmp_record_module ; 
 int /*<<< orphan*/  ngx_rtmp_record_start (TYPE_3__*) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_record_publish(ngx_rtmp_session_t *s, ngx_rtmp_publish_t *v)
{
    ngx_rtmp_record_app_conf_t     *racf;
    ngx_rtmp_record_ctx_t          *ctx;
    u_char                         *p;

    if (s->auto_pushed) {
        goto next;
    }

    racf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_record_module);

    if (racf == NULL || racf->rec.nelts == 0) {
        goto next;
    }

    if (ngx_rtmp_record_init(s) != NGX_OK) {
        return NGX_ERROR;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                   "record: publish %ui nodes",
                   racf->rec.nelts);

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_record_module);

    ngx_memcpy(ctx->name, v->name, sizeof(ctx->name));
    ngx_memcpy(ctx->args, v->args, sizeof(ctx->args));

    /* terminate name on /../ */
    for (p = ctx->name; *p; ++p) {
        if (ngx_path_separator(p[0]) &&
            p[1] == '.' && p[2] == '.' &&
            ngx_path_separator(p[3]))
        {
            *p = 0;
            break;
        }
    }

    ngx_rtmp_record_start(s);

next:
    return next_publish(s, v);
}