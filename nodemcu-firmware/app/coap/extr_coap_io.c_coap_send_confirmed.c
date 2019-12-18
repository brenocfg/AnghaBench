#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct espconn {int dummy; } ;
typedef  scalar_t__ coap_tid_t ;
typedef  int /*<<< orphan*/  coap_tick_t ;
struct TYPE_5__ {scalar_t__ id; int timeout; int t; int /*<<< orphan*/ * pdu; struct espconn* pconn; scalar_t__ retransmit_cnt; } ;
typedef  TYPE_1__ coap_queue_t ;
typedef  int /*<<< orphan*/  coap_pdu_t ;

/* Variables and functions */
 int COAP_DEFAULT_RESPONSE_TIMEOUT ; 
 scalar_t__ COAP_INVALID_TID ; 
 int COAP_TICKS_PER_SECOND ; 
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 int /*<<< orphan*/  coap_free_node (TYPE_1__*) ; 
 int /*<<< orphan*/  coap_insert_node (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* coap_new_node () ; 
 scalar_t__ coap_send (struct espconn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  coap_timer_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  coap_timer_stop () ; 
 int /*<<< orphan*/  coap_timer_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gQueue ; 
 int rand () ; 

coap_tid_t coap_send_confirmed(struct espconn *pesp_conn, coap_pdu_t *pdu) {
  coap_queue_t *node;
  coap_tick_t diff;
  uint32_t r;

  node = coap_new_node();
  if (!node) {
    NODE_DBG("coap_send_confirmed: insufficient memory\n");
    return COAP_INVALID_TID;
  }

  node->retransmit_cnt = 0;
  node->id = coap_send(pesp_conn, pdu);
  if (COAP_INVALID_TID == node->id) {
    NODE_DBG("coap_send_confirmed: error sending pdu\n");
    coap_free_node(node);
    return COAP_INVALID_TID;
  }
  r = rand();

  /* add randomized RESPONSE_TIMEOUT to determine retransmission timeout */
  node->timeout = COAP_DEFAULT_RESPONSE_TIMEOUT * COAP_TICKS_PER_SECOND +
    (COAP_DEFAULT_RESPONSE_TIMEOUT >> 1) *
    ((COAP_TICKS_PER_SECOND * (r & 0xFF)) >> 8);

  node->pconn = pesp_conn;
  node->pdu = pdu;

  /* Set timer for pdu retransmission. If this is the first element in
   * the retransmission queue, the base time is set to the current
   * time and the retransmission time is node->timeout. If there is
   * already an entry in the sendqueue, we must check if this node is
   * to be retransmitted earlier. Therefore, node->timeout is first
   * normalized to the timeout and then inserted into the queue with
   * an adjusted relative time.
   */
  coap_timer_stop();
  coap_timer_update(&gQueue);
  node->t = node->timeout;
  coap_insert_node(&gQueue, node);
  coap_timer_start(&gQueue);
  return node->id;
}