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
struct mg_mgr {int dummy; } ;
struct mg_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  coap_handler ; 
 struct mg_connection* mg_bind (struct mg_mgr*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_poll (struct mg_mgr*,int) ; 
 int /*<<< orphan*/  mg_set_protocol_coap (struct mg_connection*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* s_default_address ; 
 int s_sig_received ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_handler ; 

int main(void) {
  struct mg_mgr mgr;
  struct mg_connection *nc;

  signal(SIGTERM, signal_handler);
  signal(SIGINT, signal_handler);

  mg_mgr_init(&mgr, 0);

  nc = mg_bind(&mgr, s_default_address, coap_handler);
  if (nc == NULL) {
    printf("Unable to start listener at %s\n", s_default_address);
    return -1;
  }

  printf("Listening for CoAP messages at %s\n", s_default_address);

  mg_set_protocol_coap(nc);

  while (!s_sig_received) {
    mg_mgr_poll(&mgr, 1000000);
  }

  printf("Exiting on signal %d\n", s_sig_received);

  mg_mgr_free(&mgr);
  return 0;
}