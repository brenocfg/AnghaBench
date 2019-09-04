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
struct MPContext {int /*<<< orphan*/  input; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 struct MPContext* get_mpctx (int /*<<< orphan*/ *) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_input_set_section_mouse_area (int /*<<< orphan*/ ,char*,int,int,int,int) ; 

__attribute__((used)) static int script_input_set_section_mouse_area(lua_State *L)
{
    struct MPContext *mpctx = get_mpctx(L);

    char *section = (char *)luaL_checkstring(L, 1);
    int x0 = luaL_checkinteger(L, 2);
    int y0 = luaL_checkinteger(L, 3);
    int x1 = luaL_checkinteger(L, 4);
    int y1 = luaL_checkinteger(L, 5);
    mp_input_set_section_mouse_area(mpctx->input, section, x0, y0, x1, y1);
    return 0;
}