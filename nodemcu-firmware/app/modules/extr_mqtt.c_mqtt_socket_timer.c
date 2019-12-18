#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  msg_queue_t ;
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ mqtt_message_t ;
struct TYPE_9__ {int /*<<< orphan*/  pending_msg_q; int /*<<< orphan*/  mqtt_connection; TYPE_1__* connect_info; } ;
struct TYPE_11__ {scalar_t__ event_timeout; scalar_t__ connState; scalar_t__ keep_alive_tick; int keepalive_sent; int /*<<< orphan*/ * pesp_conn; TYPE_2__ mqtt_state; scalar_t__ secure; int /*<<< orphan*/  mqttTimer; } ;
typedef  TYPE_4__ lmqtt_userdata ;
struct TYPE_8__ {scalar_t__ keepalive; } ;

/* Variables and functions */
 int MQTT_BUF_SIZE ; 
 scalar_t__ MQTT_CONNECT_SENDING ; 
 scalar_t__ MQTT_CONNECT_SENT ; 
 int /*<<< orphan*/  MQTT_CONN_FAIL_SERVER_NOT_FOUND ; 
 int /*<<< orphan*/  MQTT_CONN_FAIL_TIMEOUT_RECEIVING ; 
 int /*<<< orphan*/  MQTT_CONN_FAIL_TIMEOUT_SENDING ; 
 scalar_t__ MQTT_DATA ; 
 scalar_t__ MQTT_INIT ; 
 int /*<<< orphan*/  MQTT_MSG_TYPE_PINGREQ ; 
 int /*<<< orphan*/  NODE_DBG (char*,...) ; 
 int /*<<< orphan*/  espconn_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  espconn_secure_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mqtt_connack_fail (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mqtt_get_qos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mqtt_msg_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_3__* mqtt_msg_pingreq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mqtt_send_if_possible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mqtt_socket_reconnected (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * msg_enqueue (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * msg_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_timer_disarm (int /*<<< orphan*/ *) ; 

void mqtt_socket_timer(void *arg)
{
  NODE_DBG("enter mqtt_socket_timer.\n");
  lmqtt_userdata *mud = (lmqtt_userdata*) arg;

  if(mud == NULL)
    return;
  if(mud->pesp_conn == NULL){
    NODE_DBG("mud->pesp_conn is NULL.\n");
    os_timer_disarm(&mud->mqttTimer);
    return;
  }

  NODE_DBG("timer, queue size: %d\n", msg_size(&(mud->mqtt_state.pending_msg_q)));
  if(mud->event_timeout > 0){
    NODE_DBG("event_timeout: %d.\n", mud->event_timeout);
        mud->event_timeout --;
    if(mud->event_timeout > 0){
      return;
    } else {
      NODE_DBG("event timeout. \n");
      if(mud->connState == MQTT_DATA)
        msg_destroy(msg_dequeue(&(mud->mqtt_state.pending_msg_q)));
      // should remove the head of the queue and re-send with DUP = 1
      // Not implemented yet.
    }
  }

  if(mud->connState == MQTT_INIT){ // socket connect time out.
    NODE_DBG("Can not connect to broker.\n");
    os_timer_disarm(&mud->mqttTimer);
    mqtt_connack_fail(mud, MQTT_CONN_FAIL_SERVER_NOT_FOUND);
#ifdef CLIENT_SSL_ENABLE
    if(mud->secure)
    {
      espconn_secure_disconnect(mud->pesp_conn);
    }
    else
#endif
    {
      espconn_disconnect(mud->pesp_conn);
    }
  } else if(mud->connState == MQTT_CONNECT_SENDING){ // MQTT_CONNECT send time out.
    NODE_DBG("sSend MQTT_CONNECT failed.\n");
    mud->connState = MQTT_INIT;
    mqtt_connack_fail(mud, MQTT_CONN_FAIL_TIMEOUT_SENDING);

#ifdef CLIENT_SSL_ENABLE
    if(mud->secure)
    {
      espconn_secure_disconnect(mud->pesp_conn);
    }
    else
#endif
    {
      espconn_disconnect(mud->pesp_conn);
    }
    mud->keep_alive_tick = 0; // not need count anymore
  } else if(mud->connState == MQTT_CONNECT_SENT) { // wait for CONACK time out.
    NODE_DBG("MQTT_CONNECT timeout.\n");
    mud->connState = MQTT_INIT;

#ifdef CLIENT_SSL_ENABLE
    if(mud->secure)
    {
      espconn_secure_disconnect(mud->pesp_conn);
    }
    else
#endif
    {
      espconn_disconnect(mud->pesp_conn);
    }
    mqtt_connack_fail(mud, MQTT_CONN_FAIL_TIMEOUT_RECEIVING);
  } else if(mud->connState == MQTT_DATA){
    msg_queue_t *pending_msg = msg_peek(&(mud->mqtt_state.pending_msg_q));
    if(pending_msg){
      mqtt_send_if_possible(mud->pesp_conn);
    } else {
      // no queued event.
      mud->keep_alive_tick ++;
      if(mud->keep_alive_tick > mud->mqtt_state.connect_info->keepalive){
        if (mud->keepalive_sent) {
          // Oh dear -- keepalive timer expired and still no ack of previous message
          mqtt_socket_reconnected(mud->pesp_conn, 0);
        } else {
          uint8_t temp_buffer[MQTT_BUF_SIZE];
          mqtt_msg_init(&mud->mqtt_state.mqtt_connection, temp_buffer, MQTT_BUF_SIZE);
          NODE_DBG("\r\nMQTT: Send keepalive packet\r\n");
          mqtt_message_t* temp_msg = mqtt_msg_pingreq(&mud->mqtt_state.mqtt_connection);
          msg_queue_t *node = msg_enqueue( &(mud->mqtt_state.pending_msg_q), temp_msg,
                              0, MQTT_MSG_TYPE_PINGREQ, (int)mqtt_get_qos(temp_msg->data) );
          mud->keepalive_sent = 1;
          mud->keep_alive_tick = 0;     // Need to reset to zero in case flow control stopped.
          mqtt_send_if_possible(mud->pesp_conn);
        }
      }
    }
  }
  NODE_DBG("keep_alive_tick: %d\n", mud->keep_alive_tick);
  NODE_DBG("leave mqtt_socket_timer.\n");
}