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
 int /*<<< orphan*/  calldata_set_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  defer_call_post (int /*<<< orphan*/ ,struct lua_obs_callback*) ; 
 int /*<<< orphan*/  defer_connect ; 
 int handler ; 
 int /*<<< orphan*/  is_function (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ls_get_libobs_obj (int,int,int*) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int signal_handler_t ; 

__attribute__((used)) static int obs_lua_signal_handler_connect(lua_State *script)
{
	signal_handler_t *handler;
	const char *signal;

	if (!ls_get_libobs_obj(signal_handler_t, 1, &handler))
		return 0;
	signal = lua_tostring(script, 2);
	if (!signal)
		return 0;
	if (!is_function(script, 3))
		return 0;

	struct lua_obs_callback *cb = add_lua_obs_callback(script, 3);
	calldata_set_ptr(&cb->base.extra, "handler", handler);
	calldata_set_string(&cb->base.extra, "signal", signal);
	defer_call_post(defer_connect, cb);
	return 0;
}