#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ len; TYPE_3__* p; } ;
struct TYPE_7__ {scalar_t__ len; TYPE_3__* p; } ;
struct TYPE_8__ {TYPE_1__ msg; struct TYPE_8__* pkt; TYPE_2__ scratch; } ;
typedef  TYPE_3__ coap_pdu_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 

void coap_delete_pdu(coap_pdu_t *pdu){
  if(!pdu)
    return;

  if(pdu->scratch.p){
    free(pdu->scratch.p);
    pdu->scratch.p = NULL;
    pdu->scratch.len = 0;
  }

  if(pdu->pkt){
    free(pdu->pkt);
    pdu->pkt = NULL;
  }

  if(pdu->msg.p){
    free(pdu->msg.p);
    pdu->msg.p = NULL;
    pdu->msg.len = 0;
  }

  free(pdu);
  pdu = NULL;
}