#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int sent_begin; size_t size; int sent_end; char const* s; } ;
typedef  TYPE_1__ ngx_http_lua_clfactory_buffer_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 char const* CLFACTORY_BEGIN_CODE ; 
 size_t CLFACTORY_BEGIN_SIZE ; 
 char const* CLFACTORY_END_CODE ; 
 size_t CLFACTORY_END_SIZE ; 

__attribute__((used)) static const char *
ngx_http_lua_clfactory_getS(lua_State *L, void *ud, size_t *size)
{
    ngx_http_lua_clfactory_buffer_ctx_t      *ls = ud;

#ifndef OPENRESTY_LUAJIT
    if (ls->sent_begin == 0) {
        ls->sent_begin = 1;
        *size = CLFACTORY_BEGIN_SIZE;

        return CLFACTORY_BEGIN_CODE;
    }
#endif

    if (ls->size == 0) {
#ifndef OPENRESTY_LUAJIT
        if (ls->sent_end == 0) {
            ls->sent_end = 1;
            *size = CLFACTORY_END_SIZE;
            return CLFACTORY_END_CODE;
        }
#endif

        return NULL;
    }

    *size = ls->size;
    ls->size = 0;

    return ls->s;
}