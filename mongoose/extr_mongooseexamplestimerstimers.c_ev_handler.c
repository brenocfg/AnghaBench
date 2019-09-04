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
struct mg_connection {int dummy; } ;
struct http_message {int dummy; } ;

/* Variables and functions */
#define  MG_EV_HTTP_REQUEST 129 
#define  MG_EV_TIMER 128 
 int /*<<< orphan*/  mg_serve_http (struct mg_connection*,struct http_message*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_set_timer (struct mg_connection*,double) ; 
 int /*<<< orphan*/  printf (char*,double) ; 
 int /*<<< orphan*/  s_http_server_opts ; 

__attribute__((used)) static void ev_handler(struct mg_connection *c, int ev, void *ev_data) {
  switch (ev) {
    case MG_EV_HTTP_REQUEST:
      mg_serve_http(c, (struct http_message *) ev_data, s_http_server_opts);
      break;
    case MG_EV_TIMER: {
      double now = *(double *) ev_data;
      double next = mg_set_timer(c, 0) + 0.5;
      printf("timer event, current time: %.2lf\n", now);
      mg_set_timer(c, next);  // Send us timer event again after 0.5 seconds
      break;
    }
  }
}