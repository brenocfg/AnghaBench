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
struct mg_connection {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int MG_EV_HTTP_REQUEST ; 
 int /*<<< orphan*/  MG_F_SEND_AND_CLOSE ; 
 int /*<<< orphan*/  mg_printf (struct mg_connection*,char*,char*) ; 
 int /*<<< orphan*/  mg_send_response_line (struct mg_connection*,int,char*) ; 

__attribute__((used)) static void secret_endpoint_cb(struct mg_connection *nc, int ev,
                               void *ev_data) {
  if (ev != MG_EV_HTTP_REQUEST) return;
  mg_send_response_line(nc, 200, "Content-Type: text/plain\r\n");
  mg_printf(nc, "%s", "Secret!");
  nc->flags |= MG_F_SEND_AND_CLOSE;
  (void) ev_data;
}