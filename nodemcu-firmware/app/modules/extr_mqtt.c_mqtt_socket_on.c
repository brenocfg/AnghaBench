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
struct TYPE_3__ {void* cb_unsuback_ref; void* cb_suback_ref; void* cb_puback_ref; void* cb_overflow_ref; void* cb_message_ref; void* cb_disconnect_ref; void* cb_connect_ref; } ;
typedef  TYPE_1__ lmqtt_userdata ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  luaL_checkanyfunction (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 void* luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int mqtt_socket_on( lua_State* L )
{
  NODE_DBG("enter mqtt_socket_on.\n");
  lmqtt_userdata *mud;
  size_t sl;

  mud = (lmqtt_userdata *)luaL_checkudata(L, 1, "mqtt.socket");
  luaL_argcheck(L, mud, 1, "mqtt.socket expected");
  if(mud==NULL){
    NODE_DBG("userdata is nil.\n");
    return 0;
  }

  const char *method = luaL_checklstring( L, 2, &sl );
  if (method == NULL)
    return luaL_error( L, "wrong arg type" );

  luaL_checkanyfunction(L, 3);
  lua_pushvalue(L, 3);  // copy argument (func) to the top of stack

  if( sl == 7 && strcmp(method, "connect") == 0){
    luaL_unref(L, LUA_REGISTRYINDEX, mud->cb_connect_ref);
    mud->cb_connect_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  }else if( sl == 7 && strcmp(method, "offline") == 0){
    luaL_unref(L, LUA_REGISTRYINDEX, mud->cb_disconnect_ref);
    mud->cb_disconnect_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  }else if( sl == 7 && strcmp(method, "message") == 0){
    luaL_unref(L, LUA_REGISTRYINDEX, mud->cb_message_ref);
    mud->cb_message_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  }else if( sl == 8 && strcmp(method, "overflow") == 0){
    luaL_unref(L, LUA_REGISTRYINDEX, mud->cb_overflow_ref);
    mud->cb_overflow_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  }else if( sl == 6 && strcmp(method, "puback") == 0){
    luaL_unref(L, LUA_REGISTRYINDEX, mud->cb_puback_ref);
    mud->cb_puback_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  }else if( sl == 6 && strcmp(method, "suback") == 0){
    luaL_unref(L, LUA_REGISTRYINDEX, mud->cb_suback_ref);
    mud->cb_suback_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  }else if( sl == 8 && strcmp(method, "unsuback") == 0){
    luaL_unref(L, LUA_REGISTRYINDEX, mud->cb_unsuback_ref);
    mud->cb_unsuback_ref = luaL_ref(L, LUA_REGISTRYINDEX);
  }else{
    lua_pop(L, 1);
    return luaL_error( L, "method not supported" );
  }
  NODE_DBG("leave mqtt_socket_on.\n");
  return 0;
}