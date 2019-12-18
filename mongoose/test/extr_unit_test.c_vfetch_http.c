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
typedef  int /*<<< orphan*/  va_list ;
struct mg_mgr {int dummy; } ;
struct mg_http_endpoint_opts {char const* auth_file; char* auth_domain; } ;
struct mg_connection {char* user_data; } ;
typedef  int /*<<< orphan*/  local_addr ;
typedef  int /*<<< orphan*/  ep_opts ;

/* Variables and functions */
 int /*<<< orphan*/  c_str_ne ; 
 int /*<<< orphan*/  cb1 ; 
 int /*<<< orphan*/  cb8 ; 
 int /*<<< orphan*/  memset (struct mg_http_endpoint_opts*,int /*<<< orphan*/ ,int) ; 
 struct mg_connection* mg_bind (struct mg_mgr*,char*,int /*<<< orphan*/ ) ; 
 struct mg_connection* mg_connect (struct mg_mgr*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_register_http_endpoint_opt (struct mg_connection*,char*,int /*<<< orphan*/ ,struct mg_http_endpoint_opts) ; 
 int /*<<< orphan*/  mg_set_protocol_http_websocket (struct mg_connection*) ; 
 int /*<<< orphan*/  mg_vprintf (struct mg_connection*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_until (struct mg_mgr*,int,int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  s_listening_port ; 
 int /*<<< orphan*/  secret_endpoint_cb ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vfetch_http(char *buf, const char *auth_file,
                        const char *request_fmt, va_list ap) {
  struct mg_mgr mgr;
  struct mg_connection *nc;
  struct mg_http_endpoint_opts ep_opts;
  char local_addr[50];

  /* Setup server. Use different local port for the next invocation. */
  mg_mgr_init(&mgr, NULL);
  /* mgr.hexdump_file = "-"; */
  snprintf(local_addr, sizeof(local_addr), "127.0.0.1:%d", s_listening_port++);
  nc = mg_bind(&mgr, local_addr, cb1);
  mg_set_protocol_http_websocket(nc);
  memset(&ep_opts, 0, sizeof(ep_opts));
  ep_opts.auth_file = auth_file;
  ep_opts.auth_domain = "foo.com";
  mg_register_http_endpoint_opt(nc, "/secret", secret_endpoint_cb, ep_opts);

  /* Setup client */
  nc = mg_connect(&mgr, local_addr, cb8);
  mg_set_protocol_http_websocket(nc);
  nc->user_data = buf;
  mg_vprintf(nc, request_fmt, ap);

  /* Run event loop, destroy server */
  buf[0] = '\0';
  poll_until(&mgr, 5, c_str_ne, buf, (void *) "");

  mg_mgr_free(&mgr);
}