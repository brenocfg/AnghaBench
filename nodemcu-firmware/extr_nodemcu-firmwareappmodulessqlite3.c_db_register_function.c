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
struct TYPE_6__ {int aggregate; void* fn_finalize; void* udata; void* fn_step; struct TYPE_6__* next; TYPE_2__* db; } ;
typedef  TYPE_1__ sdb_func ;
struct TYPE_7__ {TYPE_1__* func; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ sdb ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 void* LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  LUA_TFUNCTION ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 int /*<<< orphan*/  c_free (TYPE_1__*) ; 
 scalar_t__ c_malloc (int) ; 
 int /*<<< orphan*/ * db_sql_finalize_function ; 
 int /*<<< orphan*/ * db_sql_normal_function ; 
 TYPE_2__* lsqlite_checkdb (int /*<<< orphan*/ *,int) ; 
 int luaL_checkint (int /*<<< orphan*/ *,int) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 void* luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settop (int /*<<< orphan*/ *,int) ; 
 int sqlite3_create_function (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int db_register_function(lua_State *L, int aggregate) {
    sdb *db = lsqlite_checkdb(L, 1);
    const char *name;
    int args;
    int result;
    sdb_func *func;

    /* safety measure */
    if (aggregate) aggregate = 1;

    name = luaL_checkstring(L, 2);
    args = luaL_checkint(L, 3);
    luaL_checktype(L, 4, LUA_TFUNCTION);
    if (aggregate) luaL_checktype(L, 5, LUA_TFUNCTION);

    /* maybe an alternative way to allocate memory should be used/avoided */
    func = (sdb_func*)c_malloc(sizeof(sdb_func));
    if (func == NULL) {
        luaL_error(L, "out of memory");
    }

    result = sqlite3_create_function(
        db->db, name, args, SQLITE_UTF8, func,
        aggregate ? NULL : db_sql_normal_function,
        aggregate ? db_sql_normal_function : NULL,
        aggregate ? db_sql_finalize_function : NULL
    );

    if (result == SQLITE_OK) {
        /* safety measures for userdata field to be present in the stack */
        lua_settop(L, 5 + aggregate);

        /* save registered function in db function list */
        func->db = db;
        func->aggregate = aggregate;
        func->next = db->func;
        db->func = func;

        /* save the setp/normal function callback */
        lua_pushvalue(L, 4);
        func->fn_step = luaL_ref(L, LUA_REGISTRYINDEX);
        /* save user data */
        lua_pushvalue(L, 5+aggregate);
        func->udata = luaL_ref(L, LUA_REGISTRYINDEX);

        if (aggregate) {
            lua_pushvalue(L, 5);
            func->fn_finalize = luaL_ref(L, LUA_REGISTRYINDEX);
        }
        else
            func->fn_finalize = LUA_NOREF;
    }
    else {
        /* free allocated memory */
        c_free(func);
    }

    lua_pushboolean(L, result == SQLITE_OK ? 1 : 0);
    return 1;
}