#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* tcp; } ;
struct espconn {TYPE_3__ proto; scalar_t__ reverse; } ;
typedef  int /*<<< orphan*/  sint8_t ;
struct TYPE_6__ {scalar_t__ auto_reconnect; int /*<<< orphan*/  port; } ;
struct TYPE_9__ {TYPE_1__ mqtt_state; scalar_t__ event_timeout; int /*<<< orphan*/  mqttTimer; } ;
typedef  TYPE_4__ lmqtt_userdata ;
struct TYPE_7__ {int /*<<< orphan*/  local_port; int /*<<< orphan*/  remote_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  MQTT_CONN_FAIL_SERVER_NOT_FOUND ; 
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 scalar_t__ RECONNECT_ON ; 
 int /*<<< orphan*/  espconn_disconnect (struct espconn*) ; 
 int /*<<< orphan*/  espconn_port () ; 
 int /*<<< orphan*/  mqtt_connack_fail (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mqtt_socket_disconnected (void*) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_connect (struct espconn*) ; 

__attribute__((used)) static void mqtt_socket_reconnected(void *arg, sint8_t err)
{
  NODE_DBG("enter mqtt_socket_reconnected.\n");
  // mqtt_socket_disconnected(arg);
  struct espconn *pesp_conn = arg;
  if(pesp_conn == NULL)
    return;
  lmqtt_userdata *mud = (lmqtt_userdata *)pesp_conn->reverse;
  if(mud == NULL)
    return;

  os_timer_disarm(&mud->mqttTimer);

  mud->event_timeout = 0; // no need to count anymore

  if(mud->mqtt_state.auto_reconnect == RECONNECT_ON) {
    pesp_conn->proto.tcp->remote_port = mud->mqtt_state.port;
    pesp_conn->proto.tcp->local_port = espconn_port();
    socket_connect(pesp_conn);
  } else {
#ifdef CLIENT_SSL_ENABLE
    if (mud->secure) {
      espconn_secure_disconnect(pesp_conn);
    } else
#endif
    {
      espconn_disconnect(pesp_conn);
    }

    mqtt_connack_fail(mud, MQTT_CONN_FAIL_SERVER_NOT_FOUND);

    mqtt_socket_disconnected(arg);
  }
  NODE_DBG("leave mqtt_socket_reconnected.\n");
}