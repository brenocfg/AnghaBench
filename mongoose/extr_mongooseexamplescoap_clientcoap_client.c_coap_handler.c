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
struct mg_connection {int /*<<< orphan*/  flags; } ;
struct mg_coap_message {int msg_id; int /*<<< orphan*/  msg_type; } ;
typedef  int /*<<< orphan*/  cm ;

/* Variables and functions */
 int /*<<< orphan*/  MG_COAP_MSG_CON ; 
#define  MG_EV_CLOSE 131 
#define  MG_EV_COAP_ACK 130 
#define  MG_EV_COAP_RST 129 
#define  MG_EV_CONNECT 128 
 int /*<<< orphan*/  MG_F_SEND_AND_CLOSE ; 
 int /*<<< orphan*/  memset (struct mg_coap_message*,int /*<<< orphan*/ ,int) ; 
 int mg_coap_send_message (struct mg_connection*,struct mg_coap_message*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int s_time_to_exit ; 

__attribute__((used)) static void coap_handler(struct mg_connection *nc, int ev, void *p) {
  switch (ev) {
    case MG_EV_CONNECT: {
      struct mg_coap_message cm;
      uint32_t res;

      memset(&cm, 0, sizeof(cm));
      cm.msg_id = 1;
      cm.msg_type = MG_COAP_MSG_CON;
      printf("Sending CON...\n");
      res = mg_coap_send_message(nc, &cm);
      if (res == 0) {
        printf("Sent CON with msg_id = %d\n", cm.msg_id);
      } else {
        printf("Error: %d\n", res);
        s_time_to_exit = 1;
      }
      break;
    }
    case MG_EV_COAP_ACK:
    case MG_EV_COAP_RST: {
      struct mg_coap_message *cm = (struct mg_coap_message *) p;
      printf("ACK/RST for message with msg_id = %d received\n", cm->msg_id);
      nc->flags |= MG_F_SEND_AND_CLOSE;
      s_time_to_exit = 1;
      break;
    }
    case MG_EV_CLOSE: {
      if (s_time_to_exit == 0) {
        printf("Server closed connection\n");
        s_time_to_exit = 1;
      }
      break;
    }
  }
}