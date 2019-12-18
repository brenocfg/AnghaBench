#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {int port; int /*<<< orphan*/  recv_buffer_state; scalar_t__ recv_buffer_size; int /*<<< orphan*/ * recv_buffer; TYPE_2__* connect_info; int /*<<< orphan*/ * pending_msg_q; } ;
struct TYPE_6__ {int clean_session; int keepalive; int max_message_length; scalar_t__ will_retain; scalar_t__ will_qos; scalar_t__* password; scalar_t__* username; scalar_t__* client_id; } ;
struct TYPE_7__ {TYPE_1__ mqtt_state; TYPE_2__ connect_info; int /*<<< orphan*/  connState; void* cb_puback_ref; void* cb_unsuback_ref; void* cb_suback_ref; void* cb_overflow_ref; void* cb_message_ref; void* cb_disconnect_ref; void* cb_connect_fail_ref; void* cb_connect_ref; void* self_ref; } ;
typedef  TYPE_3__ lmqtt_userdata ;

/* Variables and functions */
 int DEFAULT_MAX_MESSAGE_LENGTH ; 
 void* LUA_NOREF ; 
 int MQTT_DEFAULT_KEEPALIVE ; 
 int /*<<< orphan*/  MQTT_INIT ; 
 int /*<<< orphan*/  MQTT_RECV_NORMAL ; 
 int /*<<< orphan*/  NODE_DBG (char*,...) ; 
 scalar_t__ calloc (int,size_t) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,char*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,size_t) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  system_get_chip_id () ; 

__attribute__((used)) static int mqtt_socket_client( lua_State* L )
{
  NODE_DBG("enter mqtt_socket_client.\n");

  lmqtt_userdata *mud;
  char tempid[20] = {0};
  sprintf(tempid, "%s%x", "NodeMCU_", system_get_chip_id() );
  NODE_DBG(tempid);
  NODE_DBG("\n");

  const char *clientId = tempid, *username = NULL, *password = NULL;
  size_t idl = strlen(tempid);
  size_t unl = 0, pwl = 0;
  int keepalive = 0;
  int stack = 1;
  int clean_session = 1;
  int max_message_length = 0;
  int top = lua_gettop(L);

  // create a object
  mud = (lmqtt_userdata *)lua_newuserdata(L, sizeof(lmqtt_userdata));
  memset(mud, 0, sizeof(*mud));
  // pre-initialize it, in case of errors
  mud->self_ref = LUA_NOREF;
  mud->cb_connect_ref = LUA_NOREF;
  mud->cb_connect_fail_ref = LUA_NOREF;
  mud->cb_disconnect_ref = LUA_NOREF;

  mud->cb_message_ref = LUA_NOREF;
  mud->cb_overflow_ref = LUA_NOREF;
  mud->cb_suback_ref = LUA_NOREF;
  mud->cb_unsuback_ref = LUA_NOREF;
  mud->cb_puback_ref = LUA_NOREF;

  mud->connState = MQTT_INIT;

  // set its metatable
  luaL_getmetatable(L, "mqtt.socket");
  lua_setmetatable(L, -2);

  if( lua_isstring(L,stack) )   // deal with the clientid string
  {
    clientId = luaL_checklstring( L, stack, &idl );
    stack++;
  }

  if(lua_isnumber( L, stack ))
  {
    keepalive = luaL_checkinteger( L, stack);
    stack++;
  }

  if(keepalive == 0){
    keepalive = MQTT_DEFAULT_KEEPALIVE;
  }

  if(lua_isstring( L, stack )){
    username = luaL_checklstring( L, stack, &unl );
    stack++;
  }
  if(username == NULL)
    unl = 0;
  NODE_DBG("length username: %d\r\n", unl);

  if(lua_isstring( L, stack )){
    password = luaL_checklstring( L, stack, &pwl );
    stack++;
  }
  if(password == NULL)
    pwl = 0;
  NODE_DBG("length password: %d\r\n", pwl);

  if(lua_isnumber( L, stack ))
  {
    clean_session = luaL_checkinteger( L, stack);
    stack++;
  }

  if(clean_session > 1){
    clean_session = 1;
  }

  if(lua_isnumber( L, stack ))
  {
      max_message_length = luaL_checkinteger( L, stack);
      stack++;
  }

  if(max_message_length == 0) {
    max_message_length = DEFAULT_MAX_MESSAGE_LENGTH;
  }

  // TODO: check the zalloc result.
  mud->connect_info.client_id = (uint8_t *)calloc(1,idl+1);
  mud->connect_info.username = (uint8_t *)calloc(1,unl + 1);
  mud->connect_info.password = (uint8_t *)calloc(1,pwl + 1);
  if(!mud->connect_info.client_id || !mud->connect_info.username || !mud->connect_info.password){
    if(mud->connect_info.client_id) {
      free(mud->connect_info.client_id);
      mud->connect_info.client_id = NULL;
    }
    if(mud->connect_info.username) {
      free(mud->connect_info.username);
      mud->connect_info.username = NULL;
    }
    if(mud->connect_info.password) {
      free(mud->connect_info.password);
      mud->connect_info.password = NULL;
    }
    return luaL_error(L, "not enough memory");
  }

  memcpy(mud->connect_info.client_id, clientId, idl);
  mud->connect_info.client_id[idl] = 0;
  memcpy(mud->connect_info.username, username, unl);
  mud->connect_info.username[unl] = 0;
  memcpy(mud->connect_info.password, password, pwl);
  mud->connect_info.password[pwl] = 0;

  NODE_DBG("MQTT: Init info: %s, %s, %s\r\n", mud->connect_info.client_id, mud->connect_info.username, mud->connect_info.password);

  mud->connect_info.clean_session = clean_session;
  mud->connect_info.will_qos = 0;
  mud->connect_info.will_retain = 0;
  mud->connect_info.keepalive = keepalive;
  mud->connect_info.max_message_length = max_message_length;

  mud->mqtt_state.pending_msg_q = NULL;
  mud->mqtt_state.port = 1883;
  mud->mqtt_state.connect_info = &mud->connect_info;
  mud->mqtt_state.recv_buffer = NULL;
  mud->mqtt_state.recv_buffer_size = 0;
  mud->mqtt_state.recv_buffer_state = MQTT_RECV_NORMAL;

  NODE_DBG("leave mqtt_socket_client.\n");
  return 1;
}