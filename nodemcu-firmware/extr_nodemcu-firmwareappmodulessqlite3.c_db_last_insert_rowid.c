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
typedef  int /*<<< orphan*/  sqlite_int64 ;
struct TYPE_3__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ sdb ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  PUSH_INT64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* lsqlite_checkdb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_last_insert_rowid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int db_last_insert_rowid(lua_State *L) {
    sdb *db = lsqlite_checkdb(L, 1);
    /* conversion warning: int64 -> luaNumber */
    sqlite_int64 rowid = sqlite3_last_insert_rowid(db->db);
    PUSH_INT64(L, rowid, lua_pushfstring(L, "%ll", rowid));
    return 1;
}