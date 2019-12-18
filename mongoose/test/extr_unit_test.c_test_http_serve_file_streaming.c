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
struct mg_connection {int* user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_EQ (int,int) ; 
 int /*<<< orphan*/  c_int_ne ; 
 struct mg_connection* mg_bind (struct mg_mgr*,char const*,int /*<<< orphan*/ ) ; 
 struct mg_connection* mg_connect (struct mg_mgr*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_printf (struct mg_connection*,char*) ; 
 int /*<<< orphan*/  mg_set_protocol_http_websocket (struct mg_connection*) ; 
 int /*<<< orphan*/  poll_until (struct mg_mgr*,int,int /*<<< orphan*/ ,int*,void*) ; 
 int /*<<< orphan*/  srv1 ; 
 int /*<<< orphan*/  srv2 ; 

__attribute__((used)) static const char *test_http_serve_file_streaming(void) {
  struct mg_mgr mgr;
  struct mg_connection *lc, *nc;
  const char *local_addr = "127.0.0.1:7732";
  int status = 0;
  mg_mgr_init(&mgr, NULL);
  ASSERT((lc = mg_bind(&mgr, local_addr, srv1)) != NULL);
  mg_set_protocol_http_websocket(lc);
  ASSERT((nc = mg_connect(&mgr, local_addr, srv2)) != NULL);
  mg_set_protocol_http_websocket(nc);
  nc->user_data = &status;
  mg_printf(nc, "GET / HTTP/1.0\r\n\r\n");
  poll_until(&mgr, 30, c_int_ne, &status, (void *) 0);
  ASSERT_EQ(status, 1);
  mg_mgr_free(&mgr);
  return NULL;
}