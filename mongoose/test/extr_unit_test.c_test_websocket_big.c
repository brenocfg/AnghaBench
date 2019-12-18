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
struct mg_connection {struct big_payload_params* user_data; } ;
struct big_payload_params {char* buf; int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_STREQ (char*,char*) ; 
 int /*<<< orphan*/  c_str_ne ; 
 int /*<<< orphan*/  cb3_big ; 
 int /*<<< orphan*/  cb4_big ; 
 struct mg_connection* mg_bind (struct mg_mgr*,char const*,int /*<<< orphan*/ ) ; 
 struct mg_connection* mg_connect (struct mg_mgr*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_send_websocket_handshake (struct mg_connection*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_set_protocol_http_websocket (struct mg_connection*) ; 
 int /*<<< orphan*/  poll_until (struct mg_mgr*,int,int /*<<< orphan*/ ,char*,void*) ; 

__attribute__((used)) static const char *test_websocket_big(void) {
  struct mg_mgr mgr;
  struct mg_connection *nc;
  const char *local_addr = "127.0.0.1:7778";
  char buf[20] = "";
  struct big_payload_params params;
  params.buf = buf;

  mg_mgr_init(&mgr, NULL);
  /* mgr.hexdump_file = "-"; */
  ASSERT((nc = mg_bind(&mgr, local_addr, cb3_big)) != NULL);
  mg_set_protocol_http_websocket(nc);

  /* Websocket request */
  ASSERT((nc = mg_connect(&mgr, local_addr, cb4_big)) != NULL);
  mg_set_protocol_http_websocket(nc);
  params.size = 8192;
  nc->user_data = &params;
  params.buf[0] = '\0';
  mg_send_websocket_handshake(nc, "/ws", NULL);
  poll_until(&mgr, 1, c_str_ne, params.buf, (void *) "");

  /* Check that test buffer has been filled by the callback properly. */
  ASSERT_STREQ(buf, "success");

  /* Websocket request */
  ASSERT((nc = mg_connect(&mgr, local_addr, cb4_big)) != NULL);
  mg_set_protocol_http_websocket(nc);
  params.size = 65535;
  nc->user_data = &params;
  params.buf[0] = '\0';
  mg_send_websocket_handshake(nc, "/ws", NULL);
  poll_until(&mgr, 1, c_str_ne, params.buf, (void *) "");
  mg_mgr_free(&mgr);

  /* Check that test buffer has been filled by the callback properly. */
  ASSERT_STREQ(buf, "success");

  return NULL;
}