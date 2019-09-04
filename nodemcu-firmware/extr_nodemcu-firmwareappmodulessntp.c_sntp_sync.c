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
typedef  scalar_t__ err_t ;
struct TYPE_4__ {scalar_t__ pcb; void* list_ref; void* err_cb_ref; void* sync_cb_ref; } ;

/* Variables and functions */
 scalar_t__ ERR_ARG ; 
 scalar_t__ ERR_INPROGRESS ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  c_free (TYPE_1__*) ; 
 int /*<<< orphan*/  c_sprintf (char*,char*,int) ; 
 scalar_t__ dns_gethostbyname (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  get_free_server () ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char const*) ; 
 void* luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  lua_isnoneornil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ server_count ; 
 int /*<<< orphan*/  set_repeat_mode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sntp_dns_found ; 
 int /*<<< orphan*/  sntp_dolookups (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sntp_dosend () ; 
 TYPE_1__* state ; 
 char* state_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udp_remove (scalar_t__) ; 

__attribute__((used)) static int sntp_sync (lua_State *L)
{
  set_repeat_mode(L, 0);

  const char *errmsg = 0;
#define sync_err(x) do { errmsg = x; goto error; } while (0)

  if (state)
    return luaL_error (L, "sync in progress");

  char *state_err;
  state_err = state_init(L);
  if (state_err) {
    sync_err(state_err);
  }

  if (!lua_isnoneornil (L, 2))
  {
    lua_pushvalue (L, 2);
    state->sync_cb_ref = luaL_ref (L, LUA_REGISTRYINDEX);
  }

  if (!lua_isnoneornil (L, 3))
  {
    lua_pushvalue (L, 3);
    state->err_cb_ref = luaL_ref (L, LUA_REGISTRYINDEX);
  }

  // use last server, unless new one specified
  if (!lua_isnoneornil (L, 1))
  {
    server_count = 0;
    if (lua_istable(L, 1)) {
      // Save a reference to the table
      lua_pushvalue(L, 1);
      luaL_unref (L, LUA_REGISTRYINDEX, state->list_ref);
      state->list_ref = luaL_ref(L, LUA_REGISTRYINDEX);
      sntp_dolookups(L);
      goto good_ret;
    } else {
      size_t l;
      const char *hostname = luaL_checklstring(L, 1, &l);
      if (l>128 || hostname == NULL)
        sync_err("need <128 hostname");
      err_t err = dns_gethostbyname(hostname, get_free_server(), sntp_dns_found, state);
      if (err == ERR_INPROGRESS) {
        goto good_ret;
      } else if (err == ERR_ARG)
        sync_err("bad hostname");

      server_count++;
    }
  } else if (server_count == 0) {
    // default to ntp pool
    lua_newtable(L);
    int i;
    for (i = 0; i < 4; i++) {
      lua_pushnumber(L, i + 1);
      char buf[64];
      c_sprintf(buf, "%d.nodemcu.pool.ntp.org", i);
      lua_pushstring(L, buf);
      lua_settable(L, -3);
    }
    luaL_unref (L, LUA_REGISTRYINDEX, state->list_ref);
    state->list_ref = luaL_ref(L, LUA_REGISTRYINDEX);
    sntp_dolookups(L);
    goto good_ret;
  }

  sntp_dosend ();

good_ret:
  if (!lua_isnoneornil(L, 4)) {
    set_repeat_mode(L, 1);
  }

  return 0;

error:
  if (state)
  {
    if (state->pcb)
      udp_remove (state->pcb);
    c_free (state);
    state = 0;
  }
  return luaL_error (L, errmsg);
}