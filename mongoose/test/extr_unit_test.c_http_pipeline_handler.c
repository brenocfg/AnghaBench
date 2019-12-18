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
struct mg_connection {TYPE_1__* mgr; } ;
struct TYPE_2__ {scalar_t__ user_data; } ;

/* Variables and functions */
 int MG_EV_HTTP_REPLY ; 
 int MG_EV_HTTP_REQUEST ; 
 int /*<<< orphan*/  mg_printf (struct mg_connection*,char*) ; 
 int /*<<< orphan*/  mg_send_response_line (struct mg_connection*,int,char*) ; 

__attribute__((used)) static void http_pipeline_handler(struct mg_connection *c, int ev,
                                  void *ev_data) {
  (void) ev_data;
  int *status = (int *) c->mgr->user_data;
  if (ev == MG_EV_HTTP_REQUEST) {
    /* Server request handler */
    mg_send_response_line(c, 200,
                          "Content-Type: text/plain\r\nContent-Length: 5\r\n");
    mg_printf(c, "Hello");
    *status = *status + 1;
  } else if (ev == MG_EV_HTTP_REPLY) {
    /* Client reply handler */
    *status = *status + 10;
  }
}