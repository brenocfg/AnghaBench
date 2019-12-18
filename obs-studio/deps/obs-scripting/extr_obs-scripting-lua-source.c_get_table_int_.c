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
 int /*<<< orphan*/  UNUSED_PARAMETER (char const*) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ lua_tointeger (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int get_table_int_(lua_State *script, int idx, const char *name,
				 const char *func)
{
	int val = 0;

	lua_pushstring(script, name);
	lua_gettable(script, idx - 1);
	val = (int)lua_tointeger(script, -1);
	lua_pop(script, 1);

	UNUSED_PARAMETER(func);

	return val;
}