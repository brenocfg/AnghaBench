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
typedef  int /*<<< orphan*/  lua_State ;
typedef  scalar_t__ err_t ;
struct TYPE_3__ {scalar_t__ list_ref; int lookup_pos; } ;

/* Variables and functions */
 scalar_t__ ERR_ARG ; 
 scalar_t__ ERR_INPROGRESS ; 
 scalar_t__ LUA_NOREF ; 
 scalar_t__ LUA_REFNIL ; 
 int LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NTP_DNS_ERR ; 
 scalar_t__ dns_gethostbyname (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  get_free_server () ; 
 int /*<<< orphan*/  handle_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,int*) ; 
 int lua_objlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ server_count ; 
 int /*<<< orphan*/  sntp_dns_found ; 
 int /*<<< orphan*/  sntp_dosend () ; 
 TYPE_1__* state ; 

__attribute__((used)) static void sntp_dolookups (lua_State *L) {
  // Step through each element of the table, converting it to an address
  // at the end, start the lookups. If we have already looked everything up,
  // then move straight to sending the packets.
  if ((state->list_ref == LUA_NOREF) || (state->list_ref == LUA_REFNIL)) {
    sntp_dosend();
    return;
  }

  lua_rawgeti(L, LUA_REGISTRYINDEX, state->list_ref);
  while (1) {
    int l;

    if (lua_objlen(L, -1) <= state->lookup_pos) {
      // We reached the end
      if (server_count == 0) {
        // Oh dear -- no valid entries -- generate an error
        // This means that all the arguments are invalid. Just pick the first
        lua_rawgeti(L, -1, 1);
        const char *hostname = luaL_checklstring(L, -1, &l);
        handle_error(L, NTP_DNS_ERR, hostname);
        lua_pop(L, 1);
      } else {
        sntp_dosend();
      }
      break;
    }

    state->lookup_pos++;

    lua_rawgeti(L, -1, state->lookup_pos);

    const char *hostname = luaL_checklstring(L, -1, &l);
    lua_pop(L, 1);

    if (l>128 || hostname == NULL) {
      handle_error(L, NTP_DNS_ERR, hostname);
      break;
    }
    err_t err = dns_gethostbyname(hostname, get_free_server(), sntp_dns_found, state);
    if (err == ERR_INPROGRESS)
      break;  // Callback function sntp_dns_found will handle sntp_dosend for us
    else if (err == ERR_ARG) {
      handle_error(L, NTP_DNS_ERR, hostname);
      break;
    }
    server_count++;
  }
  lua_pop(L, 1);
}