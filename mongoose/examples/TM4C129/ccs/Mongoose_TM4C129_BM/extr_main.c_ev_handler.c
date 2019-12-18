#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mg_connection {int /*<<< orphan*/  flags; int /*<<< orphan*/  sa; } ;
struct TYPE_2__ {int /*<<< orphan*/  p; scalar_t__ len; } ;
struct http_message {TYPE_1__ uri; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int CLP_D1 ; 
 int /*<<< orphan*/  LEDWrite (int,int) ; 
#define  MG_EV_ACCEPT 130 
#define  MG_EV_CLOSE 129 
#define  MG_EV_HTTP_REQUEST 128 
 int MG_EV_POLL ; 
 int /*<<< orphan*/  MG_F_SEND_AND_CLOSE ; 
 int MG_SOCK_STRINGIFY_IP ; 
 int MG_SOCK_STRINGIFY_PORT ; 
 int /*<<< orphan*/  UARTprintf (char*,struct mg_connection*,...) ; 
 int /*<<< orphan*/  mg_printf (struct mg_connection*,char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_send_response_line (struct mg_connection*,int,char*) ; 
 int /*<<< orphan*/  mg_sock_addr_to_str (int /*<<< orphan*/ *,char*,int,int) ; 

void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
  static int led_value = 0;
  if (ev == MG_EV_POLL) return;
  // UARTprintf("%p: ev %d\r\n", nc, ev);
  switch (ev) {
    case MG_EV_ACCEPT: {
      char addr[32];
      mg_sock_addr_to_str(&nc->sa, addr, sizeof(addr),
                          MG_SOCK_STRINGIFY_IP | MG_SOCK_STRINGIFY_PORT);
      UARTprintf("%p: Connection from %s\r\n", nc, addr);
      break;
    }
    case MG_EV_HTTP_REQUEST: {
      struct http_message *hm = (struct http_message *) ev_data;
      char addr[32];
      mg_sock_addr_to_str(&nc->sa, addr, sizeof(addr),
                          MG_SOCK_STRINGIFY_IP | MG_SOCK_STRINGIFY_PORT);
      UARTprintf("%p: HTTP request\r\n", nc);
      mg_send_response_line(nc, 200,
                            "Content-Type: text/html\r\n"
                            "Connection: close");
      mg_printf(nc,
                "\r\n<h1>Hello, %s!</h1>\r\n"
                "You asked for %.*s\r\n",
                addr, (int) hm->uri.len, hm->uri.p);
      nc->flags |= MG_F_SEND_AND_CLOSE;
      led_value ^= CLP_D1;
      LEDWrite(CLP_D1, led_value);
      break;
    }
    case MG_EV_CLOSE: {
      UARTprintf("%p: Connection closed\r\n", nc);
      break;
    }
  }
}