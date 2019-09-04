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
typedef  int /*<<< orphan*/  os_param_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {scalar_t__ rate; scalar_t__ self_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_PUD () ; 
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ PCM_RATE_16K ; 
 scalar_t__ PCM_RATE_1K ; 
 int /*<<< orphan*/  PCM_RATE_8K ; 
 TYPE_1__* cfg ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 scalar_t__ luaL_optinteger (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pcm_start_play_task ; 
 scalar_t__ pud ; 
 int /*<<< orphan*/  task_post_low (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcm_drv_play( lua_State *L )
{
  GET_PUD();

  cfg->rate = luaL_optinteger( L, 2, PCM_RATE_8K );

  luaL_argcheck( L, (cfg->rate >= PCM_RATE_1K) && (cfg->rate <= PCM_RATE_16K), 2, "invalid bit rate" );

  if (cfg->self_ref == LUA_NOREF) {
    lua_pushvalue( L, 1 );  // copy self userdata to the top of stack
    cfg->self_ref = luaL_ref( L, LUA_REGISTRYINDEX );
  }

  // schedule actions for play in separate task since drv:play() might have been called
  // in the callback fn of pcm_data_play() which in turn gets called when starting play...
  task_post_low( pcm_start_play_task, (os_param_t)pud );

  return 0;
}