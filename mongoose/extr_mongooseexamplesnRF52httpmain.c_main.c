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
struct mg_bind_opts {char const** error_string; } ;
typedef  int /*<<< orphan*/  opts ;

/* Variables and functions */
 int /*<<< orphan*/  bleconfig_init () ; 
 int /*<<< orphan*/  bleconfig_poll () ; 
 int /*<<< orphan*/  cs_log_set_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_handler ; 
 int /*<<< orphan*/  memset (struct mg_bind_opts*,int,int) ; 
 struct mg_connection* mg_bind_opt (struct mg_mgr*,char*,int /*<<< orphan*/ ,struct mg_bind_opts) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_poll (struct mg_mgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_set_protocol_http_websocket (struct mg_connection*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stdout ; 

int main(void) {
  cs_log_set_file(stdout);

  bleconfig_init();

  {
    struct mg_mgr mgr;

    mg_mgr_init(&mgr, NULL);  // Initialize event manager object

    // Note that many connections can be added to a single event manager
    // Connections can be created at any point, e.g. in event handler function
    const char *err;
    struct mg_bind_opts opts;
    struct mg_connection *nc = NULL;
    memset(&opts, 0x00, sizeof(opts));
    opts.error_string = &err;
    nc = mg_bind_opt(
        &mgr, "80", ev_handler,
        opts);  // Create listening connection and add it to the event manager
    if (nc == NULL) {
      printf("Failed to create listener: %s\n", err);
      return 1;
    }
    mg_set_protocol_http_websocket(nc);

    for (;;) {  // Start infinite event loop
      bleconfig_poll();
      mg_mgr_poll(&mgr, 0);
    }

    mg_mgr_free(&mgr);
    return 0;
  }
}