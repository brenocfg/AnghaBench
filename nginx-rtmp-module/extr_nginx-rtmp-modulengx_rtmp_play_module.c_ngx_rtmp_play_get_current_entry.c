#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_play_entry_t ;
struct TYPE_7__ {size_t nentry; } ;
typedef  TYPE_2__ ngx_rtmp_play_ctx_t ;
struct TYPE_6__ {int /*<<< orphan*/ ** elts; } ;
struct TYPE_8__ {TYPE_1__ entries; } ;
typedef  TYPE_3__ ngx_rtmp_play_app_conf_t ;

/* Variables and functions */
 TYPE_3__* ngx_rtmp_get_module_app_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_rtmp_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_play_module ; 

__attribute__((used)) static ngx_rtmp_play_entry_t *
ngx_rtmp_play_get_current_entry(ngx_rtmp_session_t *s)
{
    ngx_rtmp_play_app_conf_t   *pacf;
    ngx_rtmp_play_ctx_t        *ctx;
    ngx_rtmp_play_entry_t     **ppe;

    pacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_play_module);

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_play_module);

    ppe = pacf->entries.elts;

    return ppe[ctx->nentry];
}