#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_1__ name; } ;
typedef  TYPE_2__ ngx_rtmp_relay_ctx_t ;
struct TYPE_9__ {int silent; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ ngx_rtmp_publish_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__* ngx_cpymem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ngx_min (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* ngx_rtmp_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_publish (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_rtmp_relay_module ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_relay_publish_local(ngx_rtmp_session_t *s)
{
    ngx_rtmp_publish_t          v;
    ngx_rtmp_relay_ctx_t       *ctx;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_relay_module);
    if (ctx == NULL) {
        return NGX_ERROR;
    }

    ngx_memzero(&v, sizeof(ngx_rtmp_publish_t));
    v.silent = 1;
    *(ngx_cpymem(v.name, ctx->name.data,
            ngx_min(sizeof(v.name) - 1, ctx->name.len))) = 0;

    return ngx_rtmp_publish(s, &v);
}