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
typedef  int /*<<< orphan*/  mpv_format ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_FORMAT_DOUBLE ; 
 int /*<<< orphan*/  MPV_FORMAT_FLAG ; 
 int /*<<< orphan*/  MPV_FORMAT_NODE ; 
 int /*<<< orphan*/  MPV_FORMAT_NONE ; 
 int /*<<< orphan*/  MPV_FORMAT_STRING ; 
 int /*<<< orphan*/  abort () ; 
 int luaL_checkoption (int /*<<< orphan*/ *,int,char*,char const**) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static mpv_format check_property_format(lua_State *L, int arg)
{
    if (lua_isnil(L, arg))
        return MPV_FORMAT_NONE;
    const char *fmts[] = {"none", "native", "bool", "string", "number", NULL};
    switch (luaL_checkoption(L, arg, "none", fmts)) {
    case 0: return MPV_FORMAT_NONE;
    case 1: return MPV_FORMAT_NODE;
    case 2: return MPV_FORMAT_FLAG;
    case 3: return MPV_FORMAT_STRING;
    case 4: return MPV_FORMAT_DOUBLE;
    }
    abort();
}