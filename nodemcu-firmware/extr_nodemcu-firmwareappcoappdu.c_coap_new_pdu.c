#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int len; TYPE_4__* p; } ;
struct TYPE_10__ {int len; TYPE_4__* p; } ;
struct TYPE_9__ {scalar_t__ len; int /*<<< orphan*/ * p; } ;
struct TYPE_12__ {TYPE_3__ msg; TYPE_2__ scratch; struct TYPE_12__* pkt; TYPE_1__ content; } ;
typedef  TYPE_4__ uint8_t ;
typedef  TYPE_4__ coap_pdu_t ;
typedef  TYPE_4__ coap_packet_t ;

/* Variables and functions */
 int MAX_REQUEST_SIZE ; 
 int MAX_REQ_SCRATCH_SIZE ; 
 int /*<<< orphan*/  NODE_DBG (char*) ; 
 int /*<<< orphan*/  c_free (TYPE_4__*) ; 
 scalar_t__ c_zalloc (int) ; 

coap_pdu_t * coap_new_pdu(void) {
  coap_pdu_t *pdu = NULL;
  pdu = (coap_pdu_t *)c_zalloc(sizeof(coap_pdu_t));
  if(!pdu){
    NODE_DBG("coap_new_pdu malloc error.\n");
    return NULL;
  }

  pdu->scratch.p = (uint8_t *)c_zalloc(MAX_REQ_SCRATCH_SIZE);
  if(!pdu->scratch.p){
    NODE_DBG("coap_new_pdu malloc error.\n");
    c_free(pdu);
    return NULL;
  }
  pdu->scratch.len = MAX_REQ_SCRATCH_SIZE;

  pdu->pkt = (coap_packet_t *)c_zalloc(sizeof(coap_packet_t));
  if(!pdu->pkt){
    NODE_DBG("coap_new_pdu malloc error.\n");
    c_free(pdu->scratch.p);
    c_free(pdu);
    return NULL;
  }
  pdu->pkt->content.p = NULL;
  pdu->pkt->content.len = 0;

  pdu->msg.p = (uint8_t *)c_zalloc(MAX_REQUEST_SIZE+1); // +1 for string '\0'
  if(!pdu->msg.p){
    NODE_DBG("coap_new_pdu malloc error.\n");
    c_free(pdu->pkt);
    c_free(pdu->scratch.p);
    c_free(pdu);
    return NULL;
  }
  pdu->msg.len = MAX_REQUEST_SIZE;
  return pdu;
}