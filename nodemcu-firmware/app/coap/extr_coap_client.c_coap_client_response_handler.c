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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  coap_tid_t ;
struct TYPE_11__ {scalar_t__ p; } ;
struct TYPE_10__ {scalar_t__ t; int code; } ;
struct TYPE_9__ {scalar_t__ len; int /*<<< orphan*/ * p; } ;
struct TYPE_12__ {TYPE_3__ payload; TYPE_2__ hdr; TYPE_1__ content; } ;
typedef  TYPE_4__ coap_packet_t ;

/* Variables and functions */
 int /*<<< orphan*/  COAP_INVALID_TID ; 
 int COAP_RESPONSE_CLASS (int) ; 
 scalar_t__ COAP_TYPE_CON ; 
 scalar_t__ COAP_TYPE_NONCON ; 
 scalar_t__ COAP_TYPE_RESET ; 
 int /*<<< orphan*/  NODE_DBG (char*,...) ; 
 int /*<<< orphan*/  check_token (TYPE_4__*) ; 
 int /*<<< orphan*/  coap_dumpPacket (TYPE_4__*) ; 
 int coap_parse (TYPE_4__*,char*,unsigned short) ; 
 int /*<<< orphan*/  coap_remove_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coap_timer_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  coap_timer_stop () ; 
 int /*<<< orphan*/  coap_timer_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  coap_transaction_id (int /*<<< orphan*/  const,int /*<<< orphan*/  const,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gQueue ; 

void coap_client_response_handler(char *data, unsigned short len, unsigned short size, const uint32_t ip, const uint32_t port)
{
  NODE_DBG("coap_client_response_handler is called.\n");
  coap_packet_t pkt;
  pkt.content.p = NULL;
  pkt.content.len = 0;
  int rc;

  if (0 != (rc = coap_parse(&pkt, data, len))){
    NODE_DBG("Bad packet rc=%d\n", rc);
  }
  else
  {
#ifdef COAP_DEBUG
    coap_dumpPacket(&pkt);
#endif
    /* check if this is a response to our original request */
    if (!check_token(&pkt)) {
      /* drop if this was just some message, or send RST in case of notification */
      if (pkt.hdr.t == COAP_TYPE_CON || pkt.hdr.t == COAP_TYPE_NONCON){
        // coap_send_rst(pkt);  // send RST response
        // or, just ignore it.
      }
      goto end;
    }

    if (pkt.hdr.t == COAP_TYPE_RESET) {
      NODE_DBG("got RST\n");
      goto end;
    }

    coap_tid_t id = COAP_INVALID_TID;
    coap_transaction_id(ip, port, &pkt, &id);
    /* transaction done, remove the node from queue */
    // stop timer
    coap_timer_stop();
    // remove the node
    coap_remove_node(&gQueue, id);
    // calculate time elapsed
    coap_timer_update(&gQueue);
    coap_timer_start(&gQueue);

    if (COAP_RESPONSE_CLASS(pkt.hdr.code) == 2)
    {
      /* There is no block option set, just read the data and we are done. */
      NODE_DBG("%d.%02d\t", (pkt.hdr.code >> 5), pkt.hdr.code & 0x1F);
      NODE_DBG((char *)(pkt.payload.p));
    }
    else if (COAP_RESPONSE_CLASS(pkt.hdr.code) >= 4)
    {
      NODE_DBG("%d.%02d\t", (pkt.hdr.code >> 5), pkt.hdr.code & 0x1F);
      NODE_DBG((char *)(pkt.payload.p));
    }
  }

end:
  if(!gQueue){ // if there is no node pending in the queue, disconnect from host.

  }
}