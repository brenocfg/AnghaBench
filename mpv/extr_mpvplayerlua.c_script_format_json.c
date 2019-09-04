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
 scalar_t__ json_write (char**,struct mpv_node*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  makenode (void*,struct mpv_node*,int /*<<< orphan*/ *,int) ; 
 void* mp_lua_PITA (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free_children (void*) ; 
 char* talloc_strdup (void*,char*) ; 

__attribute__((used)) static int script_format_json(lua_State *L)
{
    void *tmp = mp_lua_PITA(L);
    struct mpv_node node;
    makenode(tmp, &node, L, 1);
    char *dst = talloc_strdup(tmp, "");
    if (json_write(&dst, &node) >= 0) {
        lua_pushstring(L, dst);
        lua_pushnil(L);
    } else {
        lua_pushnil(L);
        lua_pushstring(L, "error");
    }
    talloc_free_children(tmp);
    return 2;
}