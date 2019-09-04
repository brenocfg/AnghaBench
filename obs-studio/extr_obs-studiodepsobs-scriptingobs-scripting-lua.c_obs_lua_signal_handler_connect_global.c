#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  extra; } ;
struct lua_obs_callback {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 struct lua_obs_callback* add_lua_obs_callback (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  calldata_set_ptr (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  defer_call_post (int /*<<< orphan*/ ,struct lua_obs_callback*) ; 
 int /*<<< orphan*/  defer_connect_global ; 
 int handler ; 
 int /*<<< orphan*/  is_function (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ls_get_libobs_obj (int,int,int*) ; 
 int signal_handler_t ; 

__attribute__((used)) static int obs_lua_signal_handler_connect_global(lua_State *script)
{
	signal_handler_t *handler;

	if (!ls_get_libobs_obj(signal_handler_t, 1, &handler))
		return 0;
	if (!is_function(script, 2))
		return 0;

	struct lua_obs_callback *cb = add_lua_obs_callback(script, 2);
	calldata_set_ptr(&cb->base.extra, "handler", handler);
	defer_call_post(defer_connect_global, cb);
	return 0;
}