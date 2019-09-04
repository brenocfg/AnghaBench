#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ auto_pushed; } ;
typedef  TYPE_1__ ngx_rtmp_session_t ;
struct TYPE_17__ {int /*<<< orphan*/  args; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ ngx_rtmp_publish_t ;
struct TYPE_18__ {int /*<<< orphan*/  push_exec; } ;
typedef  TYPE_3__ ngx_rtmp_exec_ctx_t ;
struct TYPE_19__ {int /*<<< orphan*/ * conf; int /*<<< orphan*/  active; } ;
typedef  TYPE_4__ ngx_rtmp_exec_app_conf_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 scalar_t__ NGX_OK ; 
 size_t NGX_RTMP_EXEC_PUBLISH ; 
 int /*<<< orphan*/  NGX_RTMP_EXEC_PUBLISHING ; 
 int /*<<< orphan*/  next_publish (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ ngx_rtmp_exec_init_ctx (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_exec_managed (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_exec_module ; 
 int /*<<< orphan*/  ngx_rtmp_exec_unmanaged (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 
 TYPE_4__* ngx_rtmp_get_module_app_conf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_rtmp_get_module_ctx (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_exec_publish(ngx_rtmp_session_t *s, ngx_rtmp_publish_t *v)
{
    ngx_rtmp_exec_ctx_t       *ctx;
    ngx_rtmp_exec_app_conf_t  *eacf;

    eacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_exec_module);

    if (eacf == NULL || !eacf->active) {
        goto next;
    }

    if (s->auto_pushed) {
        goto next;
    }

    if (ngx_rtmp_exec_init_ctx(s, v->name, v->args, NGX_RTMP_EXEC_PUBLISHING)
        != NGX_OK)
    {
        goto next;
    }

    ngx_rtmp_exec_unmanaged(s, &eacf->conf[NGX_RTMP_EXEC_PUBLISH], "publish");

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_exec_module);

    ngx_rtmp_exec_managed(s, &ctx->push_exec, "push");

next:
    return next_publish(s, v);
}