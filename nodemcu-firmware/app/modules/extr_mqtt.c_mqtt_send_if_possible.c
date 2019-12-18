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
struct espconn {scalar_t__ reverse; } ;
typedef  int /*<<< orphan*/  sint8 ;
struct TYPE_6__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_1__ msg; } ;
typedef  TYPE_3__ msg_queue_t ;
struct TYPE_7__ {int /*<<< orphan*/  pending_msg_q; } ;
struct TYPE_9__ {scalar_t__ event_timeout; TYPE_2__ mqtt_state; scalar_t__ keep_alive_tick; scalar_t__ secure; } ;
typedef  TYPE_4__ lmqtt_userdata ;

/* Variables and functions */
 int /*<<< orphan*/  ESPCONN_OK ; 
 scalar_t__ MQTT_SEND_TIMEOUT ; 
 int /*<<< orphan*/  NODE_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  espconn_secure_send (struct espconn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  espconn_send (struct espconn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* msg_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static sint8 mqtt_send_if_possible(struct espconn *pesp_conn)
{
  if(pesp_conn == NULL)
    return ESPCONN_OK;
  lmqtt_userdata *mud = (lmqtt_userdata *)pesp_conn->reverse;
  if(mud == NULL)
    return ESPCONN_OK;

  sint8 espconn_status = ESPCONN_OK;

  // This indicates if we have sent something and are waiting for something to
  // happen
  if (mud->event_timeout == 0) {
    msg_queue_t *pending_msg = msg_peek(&(mud->mqtt_state.pending_msg_q));
    if (pending_msg) {
      mud->event_timeout = MQTT_SEND_TIMEOUT;
      NODE_DBG("Sent: %d\n", pending_msg->msg.length);
#ifdef CLIENT_SSL_ENABLE
      if( mud->secure )
      {
        espconn_status = espconn_secure_send( pesp_conn, pending_msg->msg.data, pending_msg->msg.length );
      }
      else
#endif
      {
        espconn_status = espconn_send( pesp_conn, pending_msg->msg.data, pending_msg->msg.length );
      }
      mud->keep_alive_tick = 0;
    }
  }
  NODE_DBG("send_if_poss, queue size: %d\n", msg_size(&(mud->mqtt_state.pending_msg_q)));
  return espconn_status;
}