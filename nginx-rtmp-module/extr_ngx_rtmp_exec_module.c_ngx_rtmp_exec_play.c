#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
struct TYPE_9__ {int /*<<< orphan*/  name; int /*<<< orphan*/  args; } ;
typedef  TYPE_1__ ngx_rtmp_play_t ;
struct TYPE_10__ {int counter; int /*<<< orphan*/  pull_exec; } ;
typedef  TYPE_2__ ngx_rtmp_exec_pull_ctx_t ;
struct TYPE_11__ {TYPE_2__* pull; } ;
typedef  TYPE_3__ ngx_rtmp_exec_ctx_t ;
struct TYPE_12__ {int /*<<< orphan*/ * conf; int /*<<< orphan*/  active; } ;
typedef  TYPE_4__ ngx_rtmp_exec_app_conf_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 scalar_t__ NGX_OK ; 
 size_t NGX_RTMP_EXEC_PLAY ; 
 int /*<<< orphan*/  NGX_RTMP_EXEC_PLAYING ; 
 int /*<<< orphan*/  next_play (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ ngx_rtmp_exec_init_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_rtmp_exec_init_pull_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_exec_managed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_exec_module ; 
 int /*<<< orphan*/  ngx_rtmp_exec_unmanaged (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 TYPE_4__* ngx_rtmp_get_module_app_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_rtmp_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_exec_play(ngx_rtmp_session_t *s, ngx_rtmp_play_t *v)
{
    ngx_rtmp_exec_ctx_t       *ctx;
    ngx_rtmp_exec_pull_ctx_t  *pctx;
    ngx_rtmp_exec_app_conf_t  *eacf;

    eacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_exec_module);

    if (eacf == NULL || !eacf->active) {
        goto next;
    }

    if (ngx_rtmp_exec_init_ctx(s, v->name, v->args, NGX_RTMP_EXEC_PLAYING)
        != NGX_OK)
    {
        goto next;
    }

    ngx_rtmp_exec_unmanaged(s, &eacf->conf[NGX_RTMP_EXEC_PLAY], "play");

    if (ngx_rtmp_exec_init_pull_ctx(s, v->name) != NGX_OK) {
        goto next;
    }

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_exec_module);
    pctx = ctx->pull;

    if (pctx && pctx->counter == 1) {
        ngx_rtmp_exec_managed(s, &pctx->pull_exec, "pull");
    }

next:
    return next_play(s, v);
}