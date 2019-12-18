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
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int ADDR_BUF_SIZE ; 
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  ev_handler ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct mg_connection* mg_connect (struct mg_mgr*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_poll (struct mg_mgr*,int) ; 
 int /*<<< orphan*/  mg_send (struct mg_connection*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (char*) ; 

int main(int argc, char *argv[]) {
  struct mg_mgr mgr;
  char addr[ADDR_BUF_SIZE];

  mg_mgr_init(&mgr, NULL);

  if (argc != 3) {
    fprintf(stderr, "Usage: %s <server:port> <data>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  snprintf(addr, sizeof(addr), "udp://%s", argv[1]);

  fprintf(stderr, "Connecting to '%s'\n", addr);

  struct mg_connection *nc = mg_connect(&mgr, addr, ev_handler);

  if (nc == NULL) {
    fprintf(stderr, "Failed to connect");
    exit(1);
  }

  fprintf(stderr, "Sending '%s'\n", argv[2]);

  mg_send(nc, argv[2], strlen(argv[2]));

  fprintf(stderr, "Waiting for data\n");

  for (;;) {
    mg_mgr_poll(&mgr, 10);
  }
  mg_mgr_free(&mgr);

  return 0;
}