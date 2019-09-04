#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct mg_connection {int dummy; } ;
struct mg_coap_message {int msg_id; } ;

/* Variables and functions */
#define  MG_EV_COAP_ACK 131 
#define  MG_EV_COAP_CON 130 
#define  MG_EV_COAP_NOC 129 
#define  MG_EV_COAP_RST 128 
 int mg_coap_send_ack (struct mg_connection*,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void coap_handler(struct mg_connection *nc, int ev, void *p) {
  switch (ev) {
    case MG_EV_COAP_CON: {
      uint32_t res;
      struct mg_coap_message *cm = (struct mg_coap_message *) p;
      printf("CON with msg_id = %d received\n", cm->msg_id);
      res = mg_coap_send_ack(nc, cm->msg_id);
      if (res == 0) {
        printf("Successfully sent ACK for message with msg_id = %d\n",
               cm->msg_id);
      } else {
        printf("Error: %d\n", res);
      }
      break;
    }
    case MG_EV_COAP_NOC:
    case MG_EV_COAP_ACK:
    case MG_EV_COAP_RST: {
      struct mg_coap_message *cm = (struct mg_coap_message *) p;
      printf("ACK/RST/NOC with msg_id = %d received\n", cm->msg_id);
      break;
    }
  }
}