#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_5__ {int /*<<< orphan*/  main_conf; int /*<<< orphan*/  srv_conf; int /*<<< orphan*/  app_conf; } ;
typedef  TYPE_1__ ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_relay_target_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_relay_ctx_t ;
struct TYPE_6__ {int /*<<< orphan*/  main_conf; int /*<<< orphan*/  srv_conf; int /*<<< orphan*/  app_conf; } ;
typedef  TYPE_2__ ngx_rtmp_conf_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ngx_rtmp_relay_create_connection (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_rtmp_relay_ctx_t *
ngx_rtmp_relay_create_remote_ctx(ngx_rtmp_session_t *s, ngx_str_t* name,
        ngx_rtmp_relay_target_t *target)
{
    ngx_rtmp_conf_ctx_t         cctx;

    cctx.app_conf = s->app_conf;
    cctx.srv_conf = s->srv_conf;
    cctx.main_conf = s->main_conf;

    return ngx_rtmp_relay_create_connection(&cctx, name, target);
}