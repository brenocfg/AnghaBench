#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ sdb ;
struct TYPE_7__ {int /*<<< orphan*/  ref; int /*<<< orphan*/ * L; } ;
typedef  TYPE_2__ scc ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 scalar_t__ c_malloc (int) ; 
 scalar_t__ collfree ; 
 int collwrapper (TYPE_2__*,int,void const*,int,void const*) ; 
 TYPE_1__* lsqlite_checkdb (int /*<<< orphan*/ *,int) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_isfunction (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_create_collation_v2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,void*,int (*) (void*,int,void const*,int,void const*),void (*) (void*)) ; 

__attribute__((used)) static int db_create_collation(lua_State *L) {
    sdb *db=lsqlite_checkdb(L,1);
    const char *collname=luaL_checkstring(L,2);
    scc *co=NULL;
    int (*collfunc)(scc *,int,const void *,int,const void *)=NULL;
    lua_settop(L,3); /* default args to nil, and exclude extras */
    if (lua_isfunction(L,3)) collfunc=collwrapper;
    else if (!lua_isnil(L,3))
        luaL_error(L,"create_collation: function or nil expected");
    if (collfunc != NULL) {
        co=(scc *)c_malloc(sizeof(scc)); /* userdata is a no-no as it
                                          will be garbage-collected */
        if (co) {
            co->L=L;
            /* lua_settop(L,3) above means we don't need: lua_pushvalue(L,3); */
            co->ref=luaL_ref(L,LUA_REGISTRYINDEX);
        }
        else luaL_error(L,"create_collation: could not allocate callback");
    }
    sqlite3_create_collation_v2(db->db, collname, SQLITE_UTF8,
        (void *)co,
        (int(*)(void*,int,const void*,int,const void*))collfunc,
        (void(*)(void*))collfree);
    return 0;
}