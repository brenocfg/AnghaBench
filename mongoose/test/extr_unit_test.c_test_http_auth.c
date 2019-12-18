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
 int /*<<< orphan*/  ASSERT_EQ (int,int) ; 
 int /*<<< orphan*/  c_int_eq ; 
 struct mg_connection* mg_bind (struct mg_mgr*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_connect_http (struct mg_mgr*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_connect_ws (struct mg_mgr*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_set_protocol_http_websocket (struct mg_connection*) ; 
 int /*<<< orphan*/  poll_until (struct mg_mgr*,int,int /*<<< orphan*/ ,int*,void*) ; 
 int /*<<< orphan*/  test_auth_client_handler ; 
 int /*<<< orphan*/  test_auth_server_handler ; 

__attribute__((used)) static const char *test_http_auth() {
  int connected;
  struct mg_connection *nc;
  struct mg_mgr mgr;
  mg_mgr_init(&mgr, NULL);

  nc = mg_bind(&mgr, "127.0.0.1:1234", test_auth_server_handler);
  mg_set_protocol_http_websocket(nc);
  nc->user_data = &connected;

  connected = 0;
  mg_connect_http(&mgr, test_auth_client_handler,
                  "http://foo:bar@127.0.0.1:1234", NULL, NULL);
  poll_until(&mgr, 4, c_int_eq, &connected, (void *) 1);
  ASSERT_EQ(connected, 1);

  connected = 0;
  mg_connect_ws(&mgr, test_auth_client_handler, "ws://foo:bar@127.0.0.1:1234",
                NULL, NULL);
  poll_until(&mgr, 4, c_int_eq, &connected, (void *) 1);
  ASSERT_EQ(connected, 1);

  /* check that we didn't break proto or other headers */
  connected = 0;
  mg_connect_ws(&mgr, test_auth_client_handler, "ws://127.0.0.1:1234",
                "myproto", NULL);
  poll_until(&mgr, 4, c_int_eq, &connected, (void *) 2);
  ASSERT_EQ(connected, 2);

  mg_mgr_free(&mgr);
  return NULL;
}