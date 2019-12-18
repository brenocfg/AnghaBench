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
typedef  unsigned long long uint64_t ;
struct lua_obs_timer {unsigned long long interval; int /*<<< orphan*/  last_ts; } ;
struct lua_obs_callback {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 struct lua_obs_callback* add_lua_obs_callback_extra (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  defer_call_post (int /*<<< orphan*/ ,struct lua_obs_callback*) ; 
 int /*<<< orphan*/  defer_timer_init ; 
 int /*<<< orphan*/  is_function (int /*<<< orphan*/ *,int) ; 
 struct lua_obs_timer* lua_obs_callback_extra_data (struct lua_obs_callback*) ; 
 scalar_t__ lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  obs_get_video_frame_time () ; 

__attribute__((used)) static int timer_add(lua_State *script)
{
	if (!is_function(script, 1))
		return 0;
	int ms = (int)lua_tointeger(script, 2);
	if (!ms)
		return 0;

	struct lua_obs_callback *cb = add_lua_obs_callback_extra(
		script, 1, sizeof(struct lua_obs_timer));
	struct lua_obs_timer *timer = lua_obs_callback_extra_data(cb);

	timer->interval = (uint64_t)ms * 1000000ULL;
	timer->last_ts = obs_get_video_frame_time();

	defer_call_post(defer_timer_init, cb);
	return 0;
}