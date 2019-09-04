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
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_3__ {char const* s; size_t size; scalar_t__ sent_end; scalar_t__ sent_begin; } ;
typedef  TYPE_1__ ngx_http_lua_clfactory_buffer_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  ngx_http_lua_clfactory_getS ; 

ngx_int_t
ngx_http_lua_clfactory_loadbuffer(lua_State *L, const char *buff,
    size_t size, const char *name)
{
    ngx_http_lua_clfactory_buffer_ctx_t     ls;

    ls.s = buff;
    ls.size = size;
#ifndef OPENRESTY_LUAJIT
    ls.sent_begin = 0;
    ls.sent_end = 0;
#endif

    return lua_load(L, ngx_http_lua_clfactory_getS, &ls, name);
}