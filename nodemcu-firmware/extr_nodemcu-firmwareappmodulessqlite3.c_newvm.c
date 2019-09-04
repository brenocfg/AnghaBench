#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ temp; int /*<<< orphan*/ * vm; scalar_t__ has_values; scalar_t__ columns; struct TYPE_6__* db; } ;
typedef  TYPE_1__ sdb_vm ;
typedef  TYPE_1__ sdb ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite_vm_meta ; 

__attribute__((used)) static sdb_vm *newvm(lua_State *L, sdb *db) {
    sdb_vm *svm = (sdb_vm*)lua_newuserdata(L, sizeof(sdb_vm)); /* db sql svm_ud -- */

    luaL_getmetatable(L, sqlite_vm_meta);
    lua_setmetatable(L, -2);        /* set metatable */

    svm->db = db;
    svm->columns = 0;
    svm->has_values = 0;
    svm->vm = NULL;
    svm->temp = 0;

    /* add an entry on the database table: svm -> db to keep db live while svm is live */
    lua_pushlightuserdata(L, db);     /* db sql svm_ud db_lud -- */
    lua_rawget(L, LUA_REGISTRYINDEX); /* db sql svm_ud reg[db_lud] -- */
    lua_pushlightuserdata(L, svm);    /* db sql svm_ud reg[db_lud] svm_lud -- */
    lua_pushvalue(L, -5);             /* db sql svm_ud reg[db_lud] svm_lud db -- */
    lua_rawset(L, -3);                /* (reg[db_lud])[svm_lud] = db ; set the db for this vm */
    lua_pop(L, 1);                    /* db sql svm_ud -- */

    return svm;
}