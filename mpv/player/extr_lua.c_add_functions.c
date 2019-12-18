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
struct script_ctx {int /*<<< orphan*/ * state; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcclosure (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  main_fns ; 
 int /*<<< orphan*/  push_module_table (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  register_package_fns (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  script_get_property ; 
 int /*<<< orphan*/  utils_fns ; 

__attribute__((used)) static void add_functions(struct script_ctx *ctx)
{
    lua_State *L = ctx->state;

    register_package_fns(L, "mp", main_fns);

    push_module_table(L, "mp"); // mp

    lua_pushinteger(L, 0);
    lua_pushcclosure(L, script_get_property, 1);
    lua_setfield(L, -2, "get_property");

    lua_pushinteger(L, 1);
    lua_pushcclosure(L, script_get_property, 1);
    lua_setfield(L, -2, "get_property_osd");

    lua_pop(L, 1); // -

    register_package_fns(L, "mp.utils", utils_fns);
}