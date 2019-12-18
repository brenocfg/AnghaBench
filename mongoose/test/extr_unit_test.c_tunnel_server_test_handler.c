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
struct mg_connection {void* user_data; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
#define  MG_EV_CLOSE 130 
#define  MG_EV_HTTP_REQUEST 129 
#define  MG_EV_TIMER 128 
 int /*<<< orphan*/  MG_F_SEND_AND_CLOSE ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  mg_printf (struct mg_connection*,char*,char*) ; 
 int /*<<< orphan*/  mg_printf_http_chunk (struct mg_connection*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_send_http_chunk (struct mg_connection*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_set_timer (struct mg_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_time () ; 

void tunnel_server_test_handler(struct mg_connection *nc, int ev,
                                void *ev_data) {
  (void) ev_data;
  switch (ev) {
    case MG_EV_HTTP_REQUEST:
      if (nc->user_data) break;

      nc->user_data = (void *) malloc(sizeof(int));
      (*(int *) nc->user_data) = 0;
      mg_set_timer(nc, mg_time() + 0.01);

      mg_printf(nc, "%s",
                "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
      break;
    case MG_EV_TIMER:
      mg_printf_http_chunk(nc, "%d", (*(int *) nc->user_data)++);
      if (*(int *) nc->user_data == 10) {
        mg_send_http_chunk(nc, "", 0);
        nc->flags |= MG_F_SEND_AND_CLOSE;
      } else {
        mg_set_timer(nc, mg_time() + 0.01);
      }
      break;
    case MG_EV_CLOSE:
      free(nc->user_data);
    default:
      break;
  }
}