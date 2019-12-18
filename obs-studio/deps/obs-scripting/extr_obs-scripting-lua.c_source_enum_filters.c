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
 int /*<<< orphan*/  ls_get_libobs_obj (int,int,int*) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_enum_filters (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int obs_source_t ; 
 int source ; 
 int /*<<< orphan*/  source_enum_filters_proc ; 

__attribute__((used)) static int source_enum_filters(lua_State *script)
{
	obs_source_t *source;
	if (!ls_get_libobs_obj(obs_source_t, 1, &source))
		return 0;

	lua_newtable(script);
	obs_source_enum_filters(source, source_enum_filters_proc, script);
	return 1;
}