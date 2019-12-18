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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 char* cstrcache_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  warn (char*,char const*,char const*,char*) ; 

__attribute__((used)) static inline const char *get_table_string_(lua_State *script, int idx,
					    const char *name, const char *func)
{
	const char *str = "";

	lua_pushstring(script, name);
	lua_gettable(script, idx - 1);
	if (!lua_isstring(script, -1))
		warn("%s: no item '%s' of type %s", func, name, "string");
	else
		str = cstrcache_get(lua_tostring(script, -1));
	lua_pop(script, 1);

	return str;
}