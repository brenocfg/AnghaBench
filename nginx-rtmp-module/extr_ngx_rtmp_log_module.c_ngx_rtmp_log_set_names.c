#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_12__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_13__ {int /*<<< orphan*/  args; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ ngx_rtmp_log_ctx_t ;
struct TYPE_11__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_RTMP_MAX_ARGS ; 
 int /*<<< orphan*/  NGX_RTMP_MAX_NAME ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* ngx_rtmp_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_log_module ; 
 int /*<<< orphan*/  ngx_rtmp_set_ctx (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_rtmp_log_ctx_t *
ngx_rtmp_log_set_names(ngx_rtmp_session_t *s, u_char *name, u_char *args)
{
    ngx_rtmp_log_ctx_t *ctx;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_log_module);
    if (ctx == NULL) {
        ctx = ngx_pcalloc(s->connection->pool, sizeof(ngx_rtmp_log_ctx_t));
        if (ctx == NULL) {
            return NULL;
        }

        ngx_rtmp_set_ctx(s, ctx, ngx_rtmp_log_module);
    }

    ngx_memcpy(ctx->name, name, NGX_RTMP_MAX_NAME);
    ngx_memcpy(ctx->args, args, NGX_RTMP_MAX_ARGS);

    return ctx;
}