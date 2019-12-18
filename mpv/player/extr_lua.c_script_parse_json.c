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
struct mpv_node {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ json_parse (void*,struct mpv_node*,char**,int) ; 
 int /*<<< orphan*/  json_skip_whitespace (char**) ; 
 int /*<<< orphan*/  luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 
 void* mp_lua_PITA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_lua_optarg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pushnode (int /*<<< orphan*/ *,struct mpv_node*) ; 
 int /*<<< orphan*/  talloc_free_children (void*) ; 
 char* talloc_strdup (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int script_parse_json(lua_State *L)
{
    mp_lua_optarg(L, 2);
    void *tmp = mp_lua_PITA(L);
    char *text = talloc_strdup(tmp, luaL_checkstring(L, 1));
    bool trail = lua_toboolean(L, 2);
    bool ok = false;
    struct mpv_node node;
    if (json_parse(tmp, &node, &text, 32) >= 0) {
        json_skip_whitespace(&text);
        ok = !text[0] || trail;
    }
    if (ok) {
        pushnode(L, &node);
        lua_pushnil(L);
    } else {
        lua_pushnil(L);
        lua_pushstring(L, "error");
    }
    lua_pushstring(L, text);
    talloc_free_children(tmp);
    return 3;
}