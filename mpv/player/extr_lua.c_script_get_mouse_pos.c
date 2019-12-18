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
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_input_get_mouse_pos (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int script_get_mouse_pos(lua_State *L)
{
    struct MPContext *mpctx = get_mpctx(L);
    int px, py;
    mp_input_get_mouse_pos(mpctx->input, &px, &py);
    lua_pushnumber(L, px);
    lua_pushnumber(L, py);
    return 2;
}