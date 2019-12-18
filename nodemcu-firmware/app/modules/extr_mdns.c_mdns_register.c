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
typedef  int uint8_t ;
struct nodemcu_mdns_info {char* service_name; int service_port; char** txt_data; void* host_desc; void* host_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct ip_info {TYPE_1__ ip; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_TSTRING ; 
 int /*<<< orphan*/  LUA_TTABLE ; 
 int /*<<< orphan*/  SOFTAP_IF ; 
 int /*<<< orphan*/  STATION_IF ; 
 char* alloca (int) ; 
 int luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 void* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdns_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct nodemcu_mdns_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nodemcu_mdns_init (struct nodemcu_mdns_info*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  wifi_get_ip_info (int /*<<< orphan*/ ,struct ip_info*) ; 
 int wifi_get_opmode () ; 

__attribute__((used)) static int mdns_register(lua_State *L)
{
  struct nodemcu_mdns_info info;

  memset(&info, 0, sizeof(info));

  info.host_name = luaL_checkstring(L, 1);
  info.service_name = "http";
  info.service_port = 80;
  info.host_desc = info.host_name;

  if (lua_gettop(L) >= 2) {
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_pushnil(L); // first key
    int slot = 0;
    while (lua_next(L, 2) != 0 && slot < sizeof(info.txt_data) / sizeof(info.txt_data[0])) {
      luaL_checktype(L, -2, LUA_TSTRING);
      const char *key = luaL_checkstring(L, -2);

      if (strcmp(key, "port") == 0) {
	info.service_port = luaL_checknumber(L, -1);
      } else if (strcmp(key, "service") == 0) {
	info.service_name = luaL_checkstring(L, -1);
      } else if (strcmp(key, "description") == 0) {
	info.host_desc = luaL_checkstring(L, -1);
      } else {
	int len = strlen(key) + 1;
	const char *value = luaL_checkstring(L, -1);
	char *p = alloca(len + strlen(value) + 1);
	strcpy(p, key);
	strcat(p, "=");
	strcat(p, value);
	info.txt_data[slot++] = p;
      }
      lua_pop(L, 1);
    }
  }


  struct ip_info ipconfig;

  uint8_t mode = wifi_get_opmode();

  if (!wifi_get_ip_info((mode == 2) ? SOFTAP_IF : STATION_IF, &ipconfig) || !ipconfig.ip.addr) {
    return luaL_error(L, "No network connection");
  }

  // Close up the old session (if any). This cannot fail
  // so no chance of losing the memory in 'result'

  mdns_close(L);

  // Save the result as it appears that nodemcu_mdns_init needs
  // to have the data valid while it is running.

  if (!nodemcu_mdns_init(&info)) {
    mdns_close(L);
    return luaL_error(L, "Unable to start mDns daemon");
  }

  return 0;
}