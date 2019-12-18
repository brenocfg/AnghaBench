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
struct mg_connection {struct mg_connection* user_data; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  sock_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  MG_F_USER_1 ; 
 int /*<<< orphan*/  MG_F_USER_2 ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  client_handler ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 struct mg_connection* mg_add_sock (struct mg_mgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_bind (struct mg_mgr*,char*,int /*<<< orphan*/ ) ; 
 struct mg_connection* mg_connect (struct mg_mgr*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_poll (struct mg_mgr*,int) ; 
 int /*<<< orphan*/  mg_socketpair (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_start_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  server_handler ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin_thread ; 
 scalar_t__ strcmp (char*,char*) ; 

int main(int argc, char *argv[]) {
  struct mg_mgr mgr;

  if (argc != 3) {
    fprintf(stderr, "Usage: %s <port> <client|server>\n", argv[0]);
    exit(EXIT_FAILURE);
  } else if (strcmp(argv[2], "client") == 0) {
    sock_t fds[2];
    struct mg_connection *ioconn, *server_conn;

    mg_mgr_init(&mgr, NULL);

    // Connect to the pubsub server
    server_conn = mg_connect(&mgr, argv[1], client_handler);
    if (server_conn == NULL) {
      fprintf(stderr, "Cannot connect to port %s\n", argv[1]);
      exit(EXIT_FAILURE);
    }
    server_conn->flags |= MG_F_USER_2;  // Mark this as a client connection

    // Create a socketpair and give one end to the thread that reads stdin
    mg_socketpair(fds, SOCK_STREAM);
    mg_start_thread(stdin_thread, &fds[1]);

    // The other end of a pair goes inside the server
    ioconn = mg_add_sock(&mgr, fds[0], client_handler);
    ioconn->flags |= MG_F_USER_1;  // Mark this so we know this is a stdin
    ioconn->user_data = server_conn;

  } else {
    // Server code path
    mg_mgr_init(&mgr, NULL);
    mg_bind(&mgr, argv[1], server_handler);
    printf("Starting pubsub server on port %s\n", argv[1]);
  }

  for (;;) {
    mg_mgr_poll(&mgr, 1000);
  }
  mg_mgr_free(&mgr);

  return EXIT_SUCCESS;
}