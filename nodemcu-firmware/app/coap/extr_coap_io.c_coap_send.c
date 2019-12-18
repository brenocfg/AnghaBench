#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {TYPE_3__* udp; TYPE_2__* tcp; } ;
struct espconn {scalar_t__ type; TYPE_4__ proto; } ;
typedef  int /*<<< orphan*/  ip ;
typedef  int /*<<< orphan*/  coap_tid_t ;
struct TYPE_7__ {int /*<<< orphan*/  len; scalar_t__ p; } ;
struct TYPE_11__ {int /*<<< orphan*/  pkt; TYPE_1__ msg; } ;
typedef  TYPE_5__ coap_pdu_t ;
struct TYPE_9__ {int /*<<< orphan*/  remote_port; int /*<<< orphan*/  remote_ip; } ;
struct TYPE_8__ {int /*<<< orphan*/  remote_port; int /*<<< orphan*/  remote_ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  COAP_INVALID_TID ; 
 scalar_t__ ESPCONN_TCP ; 
 int /*<<< orphan*/  coap_transaction_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  espconn_sent (struct espconn*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

coap_tid_t coap_send(struct espconn *pesp_conn, coap_pdu_t *pdu) {
  coap_tid_t id = COAP_INVALID_TID;
  uint32_t ip = 0, port = 0;
  if ( !pesp_conn || !pdu )
    return id;

  espconn_sent(pesp_conn, (unsigned char *)(pdu->msg.p), pdu->msg.len);

  if(pesp_conn->type == ESPCONN_TCP){
    memcpy(&ip, pesp_conn->proto.tcp->remote_ip, sizeof(ip));
    port = pesp_conn->proto.tcp->remote_port;
  }else{
    memcpy(&ip, pesp_conn->proto.udp->remote_ip, sizeof(ip));
    port = pesp_conn->proto.udp->remote_port;
  }
  coap_transaction_id(ip, port, pdu->pkt, &id);
  return id;
}