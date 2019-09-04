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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 struct mg_connection* mg_bind (struct mg_mgr*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_poll (struct mg_mgr*,int) ; 
 int /*<<< orphan*/  mg_set_protocol_socks (struct mg_connection*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* s_listening_addr ; 
 int /*<<< orphan*/  stderr ; 

int main(void) {
  struct mg_mgr mgr;
  struct mg_connection *c;

  mg_mgr_init(&mgr, NULL);

  if ((c = mg_bind(&mgr, s_listening_addr, NULL)) == NULL) {
    fprintf(stderr, "mg_bind(%s) failed\n", s_listening_addr);
    exit(EXIT_FAILURE);
  }
  mg_set_protocol_socks(c);

  printf("Starting socks5 proxy server on %s\n", s_listening_addr);
  for (;;) {
    mg_mgr_poll(&mgr, 1000);
  }
  mg_mgr_free(&mgr);

  return 0;
}