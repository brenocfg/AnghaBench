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
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_4__ {size_t ncaptures; int* captures; int /*<<< orphan*/ * pos; int /*<<< orphan*/  log; int /*<<< orphan*/ * captures_data; scalar_t__ ip; } ;
typedef  TYPE_1__ ngx_http_lua_script_engine_t ;
struct TYPE_5__ {size_t n; } ;
typedef  TYPE_2__ ngx_http_lua_script_capture_code_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/ * ngx_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_http_lua_script_copy_capture_code(ngx_http_lua_script_engine_t *e)
{
    int                                  *cap;
    u_char                               *p, *pos;
    ngx_uint_t                            n;
    ngx_http_lua_script_capture_code_t   *code;

    code = (ngx_http_lua_script_capture_code_t *) e->ip;

    e->ip += sizeof(ngx_http_lua_script_capture_code_t);

    n = code->n;

    pos = e->pos;

    if (n < e->ncaptures) {

        cap = e->captures;
        p = e->captures_data;

        e->pos = ngx_copy(pos, &p[cap[n]], cap[n + 1] - cap[n]);
    }

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, e->log, 0,
                   "lua script capture: \"%*s\"", e->pos - pos, pos);
}