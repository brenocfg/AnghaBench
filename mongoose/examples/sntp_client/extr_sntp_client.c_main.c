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
 int /*<<< orphan*/  ev_handler ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_poll (struct mg_mgr*,int) ; 
 struct mg_connection* mg_sntp_get_time (struct mg_mgr*,int /*<<< orphan*/ ,char*) ; 
 char* s_default_server ; 
 scalar_t__ s_exit_flag ; 
 int /*<<< orphan*/  stderr ; 

int main() {
  struct mg_mgr mgr;
  struct mg_connection *c;

  mg_mgr_init(&mgr, NULL);

  c = mg_sntp_get_time(&mgr, ev_handler, s_default_server);

  if (c == NULL) {
    fprintf(stderr, "Failed to connect to %s\n", s_default_server);
    return -1;
  }

  while (s_exit_flag == 0) {
    mg_mgr_poll(&mgr, 1000);
  }

  mg_mgr_free(&mgr);

  return 0;
}