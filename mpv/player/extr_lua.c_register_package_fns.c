#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fn_entry {scalar_t__ name; int /*<<< orphan*/  fn; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcclosure (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  push_module_table (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void register_package_fns(lua_State *L, char *module,
                                 const struct fn_entry *e)
{
    push_module_table(L, module); // modtable
    for (int n = 0; e[n].name; n++) {
        lua_pushcclosure(L, e[n].fn, 0); // modtable fn
        lua_setfield(L, -2, e[n].name); // modtable
    }
    lua_pop(L, 1); // -
}