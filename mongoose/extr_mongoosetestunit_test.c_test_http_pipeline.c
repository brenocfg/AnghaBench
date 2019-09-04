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
 int /*<<< orphan*/  ASSERT (struct mg_connection*) ; 
 int /*<<< orphan*/  ASSERT_EQ (int,int) ; 
 int /*<<< orphan*/  c_int_eq ; 
 int /*<<< orphan*/  http_pipeline_handler ; 
 struct mg_connection* mg_bind (struct mg_mgr*,char const*,int /*<<< orphan*/ ) ; 
 struct mg_connection* mg_connect (struct mg_mgr*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,void*) ; 
 int /*<<< orphan*/  mg_printf (struct mg_connection*,char*) ; 
 int /*<<< orphan*/  mg_set_protocol_http_websocket (struct mg_connection*) ; 
 int /*<<< orphan*/  poll_until (struct mg_mgr*,int,int /*<<< orphan*/ ,int*,void*) ; 

__attribute__((used)) static const char *test_http_pipeline(void) {
  struct mg_mgr mgr;
  struct mg_connection *lc, *nc1;
  const char *local_addr = "127.0.0.1:7777";
  int status = 0;

  mg_mgr_init(&mgr, (void *) &status);
  ASSERT(lc = mg_bind(&mgr, local_addr, http_pipeline_handler));
  mg_set_protocol_http_websocket(lc);
  ASSERT(nc1 = mg_connect(&mgr, local_addr, http_pipeline_handler));
  mg_set_protocol_http_websocket(nc1);
  mg_printf(nc1, "GET / HTTP/1.1\r\n\r\nGET / HTTP/1.1\r\n\r\n");
  poll_until(&mgr, 1, c_int_eq, &status, (void *) 22);
  ASSERT_EQ(status, 22);
  mg_mgr_free(&mgr);
  return NULL;
}