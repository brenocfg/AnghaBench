#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_8__ {size_t len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ ngx_rtmp_exec_ctx_t ;
struct TYPE_7__ {scalar_t__ nelts; TYPE_2__* elts; } ;
struct TYPE_10__ {TYPE_1__ names; } ;
typedef  TYPE_4__ ngx_rtmp_exec_conf_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_rtmp_exec_module ; 
 TYPE_3__* ngx_rtmp_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t ngx_strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_exec_filter(ngx_rtmp_session_t *s, ngx_rtmp_exec_conf_t *ec)
{
    size_t                len;
    ngx_str_t            *v;
    ngx_uint_t            n;
    ngx_rtmp_exec_ctx_t  *ctx;

    if (ec->names.nelts == 0) {
        return NGX_OK;
    }

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_exec_module);

    len = ngx_strlen(ctx->name);

    v = ec->names.elts;
    for (n = 0; n < ec->names.nelts; n++, s++) {
        if (v->len == len && ngx_strncmp(v->data, ctx->name, len) == 0) {
            return NGX_OK;
        }
    }

    return NGX_DECLINED;
}