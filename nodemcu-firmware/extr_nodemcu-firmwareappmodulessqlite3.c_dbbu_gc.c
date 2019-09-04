#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * bu; } ;
typedef  TYPE_1__ sdb_bu ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  cleanupbu (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* lsqlite_getbu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dbbu_gc(lua_State *L) {
    sdb_bu *sbu = lsqlite_getbu(L, 1);
    if (sbu->bu != NULL) {
        cleanupbu(L, sbu);
        lua_pop(L, 1);
    }
    /* else ignore if already finished */
    return 0;
}