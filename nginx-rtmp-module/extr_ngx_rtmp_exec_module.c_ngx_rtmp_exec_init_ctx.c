#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_21__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_22__ {int managed; int /*<<< orphan*/  respawn_timeout; int /*<<< orphan*/  kill_signal; TYPE_2__* eval_ctx; int /*<<< orphan*/  eval; int /*<<< orphan*/  log; int /*<<< orphan*/ * conf; } ;
typedef  TYPE_3__ ngx_rtmp_exec_t ;
struct TYPE_23__ {int /*<<< orphan*/  respawn_timeout; int /*<<< orphan*/  kill_signal; } ;
typedef  TYPE_4__ ngx_rtmp_exec_main_conf_t ;
struct TYPE_24__ {scalar_t__ flags; int /*<<< orphan*/  args; int /*<<< orphan*/  name; int /*<<< orphan*/  push_exec; } ;
typedef  TYPE_5__ ngx_rtmp_exec_ctx_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_exec_conf_t ;
struct TYPE_25__ {scalar_t__ respawn; TYPE_7__* conf; } ;
typedef  TYPE_6__ ngx_rtmp_exec_app_conf_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_26__ {scalar_t__ nelts; int /*<<< orphan*/ * elts; } ;
typedef  TYPE_7__ ngx_array_t ;
struct TYPE_20__ {int /*<<< orphan*/  log; int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_CONF_UNSET_MSEC ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 size_t NGX_RTMP_EXEC_PUSH ; 
 int /*<<< orphan*/  NGX_RTMP_MAX_ARGS ; 
 int /*<<< orphan*/  NGX_RTMP_MAX_NAME ; 
 scalar_t__ ngx_array_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 TYPE_3__* ngx_array_push_n (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 
 TYPE_5__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_rtmp_exec_module ; 
 int /*<<< orphan*/  ngx_rtmp_exec_push_eval ; 
 TYPE_6__* ngx_rtmp_get_module_app_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_rtmp_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_rtmp_get_module_main_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_set_ctx (TYPE_2__*,TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_exec_init_ctx(ngx_rtmp_session_t *s, u_char name[NGX_RTMP_MAX_NAME],
    u_char args[NGX_RTMP_MAX_ARGS], ngx_uint_t flags)
{
    ngx_uint_t                  n;
    ngx_array_t                *push_conf;
    ngx_rtmp_exec_t            *e;
    ngx_rtmp_exec_ctx_t        *ctx;
    ngx_rtmp_exec_conf_t       *ec;
    ngx_rtmp_exec_app_conf_t   *eacf;
    ngx_rtmp_exec_main_conf_t  *emcf;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_exec_module);

    if (ctx != NULL) {
        goto done;
    }

    ctx = ngx_pcalloc(s->connection->pool, sizeof(ngx_rtmp_exec_ctx_t));

    if (ctx == NULL) {
        return NGX_ERROR;
    }

    ngx_rtmp_set_ctx(s, ctx, ngx_rtmp_exec_module);

    eacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_exec_module);

    emcf = ngx_rtmp_get_module_main_conf(s, ngx_rtmp_exec_module);

    push_conf = &eacf->conf[NGX_RTMP_EXEC_PUSH];

    if (push_conf->nelts > 0) {

        if (ngx_array_init(&ctx->push_exec, s->connection->pool,
                           push_conf->nelts,
                           sizeof(ngx_rtmp_exec_t)) != NGX_OK)
        {
            return NGX_ERROR;
        }

        e = ngx_array_push_n(&ctx->push_exec, push_conf->nelts);

        if (e == NULL) {
            return NGX_ERROR;
        }

        ec = push_conf->elts;

        for (n = 0; n < push_conf->nelts; n++, e++, ec++) {
            ngx_memzero(e, sizeof(*e));
            e->conf = ec;
            e->managed = 1;
            e->log = s->connection->log;
            e->eval = ngx_rtmp_exec_push_eval;
            e->eval_ctx = s;
            e->kill_signal = emcf->kill_signal;
            e->respawn_timeout = (eacf->respawn ? emcf->respawn_timeout :
                                  NGX_CONF_UNSET_MSEC);
        }
    }

done:

    ngx_memcpy(ctx->name, name, NGX_RTMP_MAX_NAME);
    ngx_memcpy(ctx->args, args, NGX_RTMP_MAX_ARGS);

    ctx->flags |= flags;

    return NGX_OK;
}