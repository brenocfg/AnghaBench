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
struct lwan_lua_method_info {int /*<<< orphan*/ * func; int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  lwan_lua_method ;
struct TYPE_3__ {int /*<<< orphan*/ * func; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ luaL_reg ;

/* Variables and functions */
 struct lwan_lua_method_info* __start_lwan_lua_method ; 
 struct lwan_lua_method_info const* __stop_lwan_lua_method ; 
 int /*<<< orphan*/  lua_methods ; 
 TYPE_1__* lwan_lua_method_array_append (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwan_status_critical (char*,...) ; 

__attribute__((used)) __attribute__((constructor))
__attribute__((no_sanitize_address))
static void register_lua_methods(void)
{
    extern const struct lwan_lua_method_info SECTION_START(lwan_lua_method);
    extern const struct lwan_lua_method_info SECTION_END(lwan_lua_method);
    const struct lwan_lua_method_info *info;
    luaL_reg *r;

    for (info = __start_lwan_lua_method; info < __stop_lwan_lua_method;
         info++) {
        r = lwan_lua_method_array_append(&lua_methods);
        if (!r) {
            lwan_status_critical("Could not register Lua method `%s`",
                                 info->name);
        }

        r->name = info->name;
        r->func = info->func;
    }

    r = lwan_lua_method_array_append(&lua_methods);
    if (!r)
        lwan_status_critical("Could not add Lua method sentinel");

    r->name = NULL;
    r->func = NULL;
}