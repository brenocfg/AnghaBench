#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int softAPchannel; void* lua_dbg_cb_ref; void* lua_err_cb_ref; void* lua_connected_cb_ref; scalar_t__ connecting; scalar_t__ lastStationStatus; scalar_t__ callbackDone; scalar_t__ success; } ;
typedef  TYPE_1__ enduser_setup_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENDUSER_SETUP_DEBUG (char*) ; 
 int /*<<< orphan*/  ENDUSER_SETUP_ERROR (char*,int,int /*<<< orphan*/ ) ; 
 int ENDUSER_SETUP_ERR_ALREADY_INITIALIZED ; 
 int /*<<< orphan*/  ENDUSER_SETUP_ERR_FATAL ; 
 int ENDUSER_SETUP_ERR_OUT_OF_MEMORY ; 
 void* LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ calloc (int,int) ; 
 void* luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_isnoneornil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* state ; 

__attribute__((used)) static int enduser_setup_init(lua_State *L)
{
  /* Note: Normal to not see this debug message on first invocation because debug callback is set below */
  ENDUSER_SETUP_DEBUG("enduser_setup_init");

  /* Defer errors until the bottom, so that callbacks can be set, if applicable, to handle debug and error messages */
  int ret = 0;

  if (state != NULL)
  {
    ret = ENDUSER_SETUP_ERR_ALREADY_INITIALIZED;
  }
  else
  {
    state = (enduser_setup_state_t *) calloc(1, sizeof(enduser_setup_state_t));

    if (state == NULL)
    {
      ret = ENDUSER_SETUP_ERR_OUT_OF_MEMORY;
    }
    else
    {
      memset(state, 0, sizeof(enduser_setup_state_t));

      state->lua_connected_cb_ref = LUA_NOREF;
      state->lua_err_cb_ref = LUA_NOREF;
      state->lua_dbg_cb_ref = LUA_NOREF;

      state->softAPchannel = 1;
      state->success = 0;
      state->callbackDone = 0;
      state->lastStationStatus = 0;
      state->connecting = 0;
    }
  }

  if (!lua_isnoneornil(L, 1))
  {
    lua_pushvalue(L, 1);
    state->lua_connected_cb_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  }

  if (!lua_isnoneornil(L, 2))
  {
    lua_pushvalue (L, 2);
    state->lua_err_cb_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  }

  if (!lua_isnoneornil(L, 3))
  {
    lua_pushvalue (L, 3);
    state->lua_dbg_cb_ref = luaL_ref(L, LUA_REGISTRYINDEX);
    ENDUSER_SETUP_DEBUG("enduser_setup_init: Debug callback has been set");
  }

  if (ret == ENDUSER_SETUP_ERR_ALREADY_INITIALIZED)
  {
    ENDUSER_SETUP_ERROR("init failed. Appears to already be started. EUS will shut down now.", ENDUSER_SETUP_ERR_ALREADY_INITIALIZED, ENDUSER_SETUP_ERR_FATAL);
  }
  else if (ret == ENDUSER_SETUP_ERR_OUT_OF_MEMORY)
  {
    ENDUSER_SETUP_ERROR("init failed. Unable to allocate memory.", ENDUSER_SETUP_ERR_OUT_OF_MEMORY, ENDUSER_SETUP_ERR_FATAL);
  }

  return ret;
}