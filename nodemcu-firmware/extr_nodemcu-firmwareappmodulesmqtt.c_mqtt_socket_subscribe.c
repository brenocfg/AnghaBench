#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ sint8 ;
struct TYPE_13__ {int /*<<< orphan*/  length; } ;
struct TYPE_15__ {TYPE_1__ msg; int /*<<< orphan*/  publish_qos; int /*<<< orphan*/  msg_id; } ;
typedef  TYPE_3__ msg_queue_t ;
struct TYPE_16__ {scalar_t__ length; int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ mqtt_message_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_14__ {int /*<<< orphan*/  pending_msg_q; int /*<<< orphan*/  mqtt_connection; } ;
struct TYPE_17__ {TYPE_2__ mqtt_state; int /*<<< orphan*/ * pesp_conn; int /*<<< orphan*/  event_timeout; int /*<<< orphan*/  cb_suback_ref; int /*<<< orphan*/  connected; } ;
typedef  TYPE_5__ lmqtt_userdata ;

/* Variables and functions */
 scalar_t__ ESPCONN_IF ; 
 scalar_t__ ESPCONN_OK ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ LUA_TFUNCTION ; 
 scalar_t__ LUA_TLIGHTFUNCTION ; 
 int MQTT_BUF_SIZE ; 
 int /*<<< orphan*/  MQTT_MSG_TYPE_SUBSCRIBE ; 
 int /*<<< orphan*/  NODE_DBG (char*,...) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,TYPE_5__*,int,char*) ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 scalar_t__ mqtt_get_qos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mqtt_msg_init (int /*<<< orphan*/ *,int*,int) ; 
 TYPE_4__* mqtt_msg_subscribe (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *) ; 
 TYPE_4__* mqtt_msg_subscribe_fini (int /*<<< orphan*/ *) ; 
 TYPE_4__* mqtt_msg_subscribe_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* mqtt_msg_subscribe_topic (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ mqtt_send_if_possible (int /*<<< orphan*/ *) ; 
 TYPE_3__* msg_enqueue (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mqtt_socket_subscribe( lua_State* L ) {
  NODE_DBG("enter mqtt_socket_subscribe.\n");

  uint8_t stack = 1, qos = 0;
  uint16_t msg_id = 0;
  const char *topic;
  size_t il;
  lmqtt_userdata *mud;

  mud = (lmqtt_userdata *) luaL_checkudata( L, stack, "mqtt.socket" );
  luaL_argcheck( L, mud, stack, "mqtt.socket expected" );
  stack++;

  if(mud==NULL){
    NODE_DBG("userdata is nil.\n");
    lua_pushboolean(L, 0);
    return 1;
  }

  if(mud->pesp_conn == NULL){
    NODE_DBG("mud->pesp_conn is NULL.\n");
    lua_pushboolean(L, 0);
    return 1;
  }

  if(!mud->connected){
    luaL_error( L, "not connected" );
    lua_pushboolean(L, 0);
    return 1;
  }

  uint8_t temp_buffer[MQTT_BUF_SIZE];
  mqtt_msg_init(&mud->mqtt_state.mqtt_connection, temp_buffer, MQTT_BUF_SIZE);
  mqtt_message_t *temp_msg = NULL;

  if( lua_istable( L, stack ) ) {
    NODE_DBG("subscribe table\n");
    lua_pushnil( L ); /* first key */

    int topic_count = 0;
    uint8_t overflow = 0;

    while( lua_next( L, stack ) != 0 ) {
      topic = luaL_checkstring( L, -2 );
      qos = luaL_checkinteger( L, -1 );

      if (topic_count == 0) {
        temp_msg = mqtt_msg_subscribe_init( &mud->mqtt_state.mqtt_connection, &msg_id );
      }
      temp_msg = mqtt_msg_subscribe_topic( &mud->mqtt_state.mqtt_connection, topic, qos );
      topic_count++;

      NODE_DBG("topic: %s - qos: %d, length: %d\n", topic, qos, temp_msg->length);

      if (temp_msg->length == 0) {
        lua_pop(L, 1);
        overflow = 1;
        break;  // too long message for the outbuffer.
      }

      lua_pop( L, 1 );
    }

    if (topic_count == 0){
      return luaL_error( L, "no topics found" );
    }
    if (overflow != 0){
      return luaL_error( L, "buffer overflow, can't enqueue all subscriptions" );
    }

    temp_msg = mqtt_msg_subscribe_fini( &mud->mqtt_state.mqtt_connection );
    if (temp_msg->length == 0) {
      return luaL_error( L, "buffer overflow, can't enqueue all subscriptions" );
    }

    stack++;
  } else {
    NODE_DBG("subscribe string\n");
    topic = luaL_checklstring( L, stack, &il );
    stack++;
    if( topic == NULL ){
      return luaL_error( L, "need topic name" );
    }
    qos = luaL_checkinteger( L, stack );
    temp_msg = mqtt_msg_subscribe( &mud->mqtt_state.mqtt_connection, topic, qos, &msg_id );
    stack++;
  }

  if( lua_type( L, stack ) == LUA_TFUNCTION || lua_type( L, stack ) == LUA_TLIGHTFUNCTION ) {    // TODO: this will overwrite the previous one.
    lua_pushvalue( L, stack );  // copy argument (func) to the top of stack
    luaL_unref( L, LUA_REGISTRYINDEX, mud->cb_suback_ref );
    mud->cb_suback_ref = luaL_ref( L, LUA_REGISTRYINDEX );
  }

  msg_queue_t *node = msg_enqueue( &(mud->mqtt_state.pending_msg_q), temp_msg,
                                   msg_id, MQTT_MSG_TYPE_SUBSCRIBE, (int)mqtt_get_qos(temp_msg->data) );

  NODE_DBG("topic: %s - id: %d - qos: %d, length: %d\n", topic, node->msg_id, node->publish_qos, node->msg.length);
  NODE_DBG("msg_size: %d, event_timeout: %d\n", msg_size(&(mud->mqtt_state.pending_msg_q)), mud->event_timeout);

  sint8 espconn_status = ESPCONN_IF;

  espconn_status = mqtt_send_if_possible(mud->pesp_conn);

  if(!node || espconn_status != ESPCONN_OK){
    lua_pushboolean(L, 0);
  } else {
    lua_pushboolean(L, 1);  // enqueued succeed.
  }
  NODE_DBG("subscribe, queue size: %d\n", msg_size(&(mud->mqtt_state.pending_msg_q)));
  NODE_DBG("leave mqtt_socket_subscribe.\n");
  return 1;
}