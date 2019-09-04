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
struct mg_connection {int /*<<< orphan*/  flags; scalar_t__ user_data; } ;
struct http_message {int dummy; } ;

/* Variables and functions */
 int MG_EV_HTTP_REPLY ; 
 int MG_EV_HTTP_REQUEST ; 
 int /*<<< orphan*/  MG_F_CLOSE_IMMEDIATELY ; 
 int /*<<< orphan*/  mg_http_serve_file (struct mg_connection*,struct http_message*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mk_str (char*) ; 
 int /*<<< orphan*/  serve_file_verify (struct http_message*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void serve_file_cb(struct mg_connection *nc, int ev, void *ev_data) {
  struct http_message *hm = (struct http_message *) ev_data;
  char *user_data = (char *) nc->user_data;

  if (ev == MG_EV_HTTP_REQUEST) {
    mg_http_serve_file(nc, hm, "unit_test.c", mg_mk_str("text/plain"),
                       mg_mk_str(""));
  } else if (ev == MG_EV_HTTP_REPLY) {
    strcpy(user_data, serve_file_verify(hm));
    nc->flags |= MG_F_CLOSE_IMMEDIATELY;
  }
}