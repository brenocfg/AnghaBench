#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_char ;
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
struct TYPE_3__ {int offset; } ;
typedef  TYPE_1__ ngx_rtmp_log_op_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_log_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ngx_rtmp_get_module_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_log_module ; 

__attribute__((used)) static u_char *
ngx_rtmp_log_var_context_cstring_getdata(ngx_rtmp_session_t *s, u_char *buf,
    ngx_rtmp_log_op_t *op)
{
    ngx_rtmp_log_ctx_t *ctx;
    u_char             *p;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_log_module);
    if (ctx == NULL) {
        return buf;
    }

    p = (u_char *) ctx + op->offset;
    while (*p) {
        *buf++ = *p++;
    }

    return buf;
}