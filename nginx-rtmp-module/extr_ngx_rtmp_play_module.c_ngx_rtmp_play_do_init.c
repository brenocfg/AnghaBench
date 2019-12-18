#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
struct TYPE_5__ {int /*<<< orphan*/  vindex; int /*<<< orphan*/  aindex; int /*<<< orphan*/  file; TYPE_1__* fmt; } ;
typedef  TYPE_2__ ngx_rtmp_play_ctx_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_4__ {scalar_t__ (* init ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 TYPE_2__* ngx_rtmp_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_play_module ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_play_do_init(ngx_rtmp_session_t *s)
{
    ngx_rtmp_play_ctx_t            *ctx;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_play_module);

    if (ctx == NULL) {
        return NGX_ERROR;
    }

    if (ctx->fmt && ctx->fmt->init &&
        ctx->fmt->init(s, &ctx->file, ctx->aindex, ctx->vindex) != NGX_OK)
    {
        return NGX_ERROR;
    }

    return NGX_OK;
}