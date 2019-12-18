#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct espconn {scalar_t__ reverse; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {int /*<<< orphan*/  recv_buffer_state; scalar_t__ recv_buffer_size; TYPE_4__* recv_buffer; } ;
struct TYPE_7__ {int connected; scalar_t__ cb_disconnect_ref; scalar_t__ self_ref; TYPE_4__* pesp_conn; TYPE_1__ mqtt_state; int /*<<< orphan*/  mqttTimer; } ;
typedef  TYPE_3__ lmqtt_userdata ;
struct TYPE_6__ {TYPE_4__* tcp; } ;
struct TYPE_8__ {TYPE_2__ proto; int /*<<< orphan*/ * reverse; } ;

/* Variables and functions */
 scalar_t__ LUA_NOREF ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  MQTT_RECV_NORMAL ; 
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mqtt_socket_disconnected(void *arg)    // tcp only
{
  NODE_DBG("enter mqtt_socket_disconnected.\n");
  struct espconn *pesp_conn = arg;
  bool call_back = false;
  if(pesp_conn == NULL)
    return;
  lmqtt_userdata *mud = (lmqtt_userdata *)pesp_conn->reverse;
  if(mud == NULL)
    return;

  os_timer_disarm(&mud->mqttTimer);

  lua_State *L = lua_getstate();

  if(mud->connected){     // call back only called when socket is from connection to disconnection.
    mud->connected = false;
    if((mud->cb_disconnect_ref != LUA_NOREF) && (mud->self_ref != LUA_NOREF)) {
      lua_rawgeti(L, LUA_REGISTRYINDEX, mud->cb_disconnect_ref);
      lua_rawgeti(L, LUA_REGISTRYINDEX, mud->self_ref);  // pass the userdata(client) to callback func in lua
      call_back = true;
    }
  }

  if(mud->mqtt_state.recv_buffer) {
    free(mud->mqtt_state.recv_buffer);
    mud->mqtt_state.recv_buffer = NULL;
  }
  mud->mqtt_state.recv_buffer_size = 0;
  mud->mqtt_state.recv_buffer_state = MQTT_RECV_NORMAL;

  if(mud->pesp_conn){
    mud->pesp_conn->reverse = NULL;
    if(mud->pesp_conn->proto.tcp)
      free(mud->pesp_conn->proto.tcp);
    mud->pesp_conn->proto.tcp = NULL;
    free(mud->pesp_conn);
    mud->pesp_conn = NULL;
  }

  mud->connected = false;
  luaL_unref(L, LUA_REGISTRYINDEX, mud->self_ref);
  mud->self_ref = LUA_NOREF; // unref this, and the mqtt.socket userdata will delete it self

  if(call_back){
    lua_call(L, 1, 0);
  }

  NODE_DBG("leave mqtt_socket_disconnected.\n");
}