#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; TYPE_1__ name; } ;
struct TYPE_8__ {TYPE_2__ shm; scalar_t__ data; } ;
typedef  TYPE_3__ ngx_shm_zone_t ;
typedef  int ngx_int_t ;
struct TYPE_9__ {int /*<<< orphan*/  isold; int /*<<< orphan*/  isinit; } ;
typedef  TYPE_4__ ngx_http_lua_fake_shm_ctx_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TTABLE ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 
 TYPE_3__** lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ngx_http_lua_fake_shm_get_info(lua_State *L)
{
    ngx_int_t                         n;
    ngx_shm_zone_t                   *zone;
    ngx_shm_zone_t                  **zone_udata;
    ngx_http_lua_fake_shm_ctx_t      *ctx;

    n = lua_gettop(L);

    if (n != 1) {
        return luaL_error(L, "expecting exactly one arguments, "
                          "but only seen %d", n);
    }

    luaL_checktype(L, 1, LUA_TTABLE);

    lua_rawgeti(L, 1, 1);
    zone_udata = lua_touserdata(L, -1);
    lua_pop(L, 1);

    if (zone_udata == NULL) {
        return luaL_error(L, "bad \"zone\" argument");
    }

    zone = *zone_udata;

    ctx = (ngx_http_lua_fake_shm_ctx_t *) zone->data;

    lua_pushlstring(L, (char *) zone->shm.name.data, zone->shm.name.len);
    lua_pushnumber(L, zone->shm.size);
    lua_pushboolean(L, ctx->isinit);
    lua_pushboolean(L, ctx->isold);

    return 4;
}