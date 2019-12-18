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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {scalar_t__ vu_freq; void* cb_vu_ref; void* cb_stopped_ref; void* cb_paused_ref; void* cb_drained_ref; void* cb_data_ref; } ;

/* Variables and functions */
 void* COND_REF (scalar_t__) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GET_PUD () ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ LUA_TFUNCTION ; 
 scalar_t__ LUA_TLIGHTFUNCTION ; 
 scalar_t__ TRUE ; 
 TYPE_1__* cfg ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int luaL_optinteger (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int pcm_drv_on( lua_State *L )
{
  size_t len;
  const char *event;
  uint8_t is_func = FALSE;

  GET_PUD();

  event = luaL_checklstring( L, 2, &len );

  if ((lua_type( L, 3 ) == LUA_TFUNCTION) ||
      (lua_type( L, 3 ) == LUA_TLIGHTFUNCTION)) {
    lua_pushvalue( L, 3 );  // copy argument (func) to the top of stack
    is_func = TRUE;
  }

  if ((len == 4) && (strcmp( event, "data" ) == 0)) {
    luaL_unref( L, LUA_REGISTRYINDEX, cfg->cb_data_ref);
    cfg->cb_data_ref = COND_REF( is_func );
  } else if ((len == 7) && (strcmp( event, "drained" ) == 0)) {
    luaL_unref( L, LUA_REGISTRYINDEX, cfg->cb_drained_ref);
    cfg->cb_drained_ref = COND_REF( is_func );
  } else if ((len == 6) && (strcmp( event, "paused" ) == 0)) {
    luaL_unref( L, LUA_REGISTRYINDEX, cfg->cb_paused_ref);
    cfg->cb_paused_ref = COND_REF( is_func );
  } else if ((len == 7) && (strcmp( event, "stopped" ) == 0)) {
    luaL_unref( L, LUA_REGISTRYINDEX, cfg->cb_stopped_ref);
    cfg->cb_stopped_ref = COND_REF( is_func );
  } else if ((len == 2) && (strcmp( event, "vu" ) == 0)) {
    luaL_unref( L, LUA_REGISTRYINDEX, cfg->cb_vu_ref);
    cfg->cb_vu_ref = COND_REF( is_func );

    int freq = luaL_optinteger( L, 4, 10 );
    luaL_argcheck( L, (freq > 0) && (freq <= 200), 4, "invalid range" );
    cfg->vu_freq = (uint8_t)freq;
  } else {
    if (is_func) {
      // need to pop pushed function arg
      lua_pop( L, 1 );
    }
    return luaL_error( L, "method not supported" );
  }

  return 0;
}