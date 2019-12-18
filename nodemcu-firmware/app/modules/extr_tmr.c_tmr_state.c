#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* tmr_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int mode; } ;

/* Variables and functions */
 int TIMER_IDLE_FLAG ; 
 int TIMER_MODE_OFF ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 TYPE_1__* tmr_get (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tmr_state(lua_State* L){
	tmr_t tmr = tmr_get(L, 1);

	if(tmr->mode == TIMER_MODE_OFF){
		lua_pushnil(L);
		return 1;
	}

  lua_pushboolean(L, (tmr->mode & TIMER_IDLE_FLAG) == 0);
  lua_pushinteger(L, tmr->mode & (~TIMER_IDLE_FLAG));
	return 2;
}