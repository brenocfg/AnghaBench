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
struct mg_str {char* p; int len; } ;
struct mg_mgr {int dummy; } ;
struct mg_connection {struct mbuf* user_data; } ;
struct mbuf {scalar_t__ len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_EQ (scalar_t__,int) ; 
 int /*<<< orphan*/  ASSERT_STREQ (int /*<<< orphan*/ ,char const*) ; 
 int WEBSOCKET_DONT_FIN ; 
 int WEBSOCKET_OP_CLOSE ; 
 int WEBSOCKET_OP_CONTINUE ; 
 int WEBSOCKET_OP_PING ; 
 int WEBSOCKET_OP_TEXT ; 
 int /*<<< orphan*/  c_int_eq ; 
 int /*<<< orphan*/  c_int_ne ; 
 int /*<<< orphan*/  cb_ws_client1 ; 
 int /*<<< orphan*/  cb_ws_server ; 
 int /*<<< orphan*/  mbuf_append (struct mbuf*,char*,int) ; 
 int /*<<< orphan*/  mbuf_free (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_init (struct mbuf*,int) ; 
 struct mg_connection* mg_bind (struct mg_mgr*,char const*,int /*<<< orphan*/ ) ; 
 struct mg_connection* mg_connect (struct mg_mgr*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_send_websocket_frame (struct mg_connection*,int,char*,int) ; 
 int /*<<< orphan*/  mg_send_websocket_framev (struct mg_connection*,int,struct mg_str*,int) ; 
 int /*<<< orphan*/  mg_send_websocket_handshake (struct mg_connection*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_set_protocol_http_websocket (struct mg_connection*) ; 
 int /*<<< orphan*/  poll_until (struct mg_mgr*,int,int /*<<< orphan*/ ,scalar_t__*,void*) ; 
 scalar_t__ s_ws_client1_connected ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static const char *test_websocket(void) {
  struct mg_mgr mgr;
  struct mg_connection *nc;
  const char *local_addr = "127.0.0.1:7778";
  struct mbuf mb;
  mbuf_init(&mb, 100);

  mg_mgr_init(&mgr, NULL);
  /* mgr.hexdump_file = "-"; */
  ASSERT((nc = mg_bind(&mgr, local_addr, cb_ws_server)) != NULL);
  mg_set_protocol_http_websocket(nc);

  /*
   * Websocket request "hi" via mg_send_websocket_framev()
   */
  mb.len = 0;
  s_ws_client1_connected = 0;
  ASSERT((nc = mg_connect(&mgr, local_addr, cb_ws_client1)) != NULL);
  mg_set_protocol_http_websocket(nc);
  nc->user_data = &mb;
  mg_send_websocket_handshake(nc, "/ws", NULL);
  poll_until(&mgr, 1, c_int_ne, &s_ws_client1_connected, (void *) 1);
  {
    /* Send "hi" to server. server must reply "A". */
    struct mg_str h[2];
    h[0].p = "h";
    h[0].len = 1;
    h[1].p = "i";
    h[1].len = 1;
    mg_send_websocket_framev(nc, WEBSOCKET_OP_TEXT, h, 2);
  }
  poll_until(&mgr, 1, c_int_ne, &mb.len, (void *) 0);
  mbuf_append(&mb, "\0", 1);
  /* Check that test buffer has been filled by the callback properly. */
  ASSERT_STREQ(mb.buf, "81:[81:{hi}]");

  /*
   * Websocket request "hallloo", composed from two fragments
   */
  mb.len = 0;
  s_ws_client1_connected = 0;
  ASSERT((nc = mg_connect(&mgr, local_addr, cb_ws_client1)) != NULL);
  mg_set_protocol_http_websocket(nc);
  nc->user_data = &mb;
  mg_send_websocket_handshake(nc, "/ws", NULL);
  poll_until(&mgr, 1, c_int_ne, &s_ws_client1_connected, (void *) 1);
  ASSERT_EQ(s_ws_client1_connected, 1);

  mg_send_websocket_frame(nc, WEBSOCKET_OP_TEXT | WEBSOCKET_DONT_FIN, "hall",
                          4);
  mg_send_websocket_frame(nc, WEBSOCKET_OP_CONTINUE | WEBSOCKET_DONT_FIN, "--",
                          2);

  /* Poll 0.5 seconds, we don't expect c_str_ne predicate to return true */
  poll_until(&mgr, 0.5, c_int_ne, &mb.len, (void *) 0);
  ASSERT_EQ(mb.len, 0);

  mg_send_websocket_frame(nc, WEBSOCKET_OP_CONTINUE, "loo", 3);

  poll_until(&mgr, 1, c_int_ne, &mb.len, (void *) 0);
  mbuf_append(&mb, "\0", 1);
  /* Check that test buffer has been filled by the callback properly. */
  ASSERT_STREQ(mb.buf, "81:[81:{hall--loo}]");

  /*
   * Ping request
   */
  mb.len = 0;
  s_ws_client1_connected = 0;
  ASSERT((nc = mg_connect(&mgr, local_addr, cb_ws_client1)) != NULL);
  mg_set_protocol_http_websocket(nc);
  nc->user_data = &mb;
  mg_send_websocket_handshake(nc, "/ws", NULL);
  poll_until(&mgr, 1, c_int_ne, &s_ws_client1_connected, (void *) 1);
  ASSERT_EQ(s_ws_client1_connected, 1);

  mg_send_websocket_frame(nc, WEBSOCKET_OP_PING, "myping", 6);

  {
    /*
     * As a response to Ping, we should first receive Pong (0x8a),
     * and then text message (0x81) with our Ping (0x89) echo.
     */
    const char *expected = "CONTROL:8a:[myping]81:[CONTROL:89:{myping}]";
    poll_until(&mgr, 1, c_int_eq, &mb.len, (void *) strlen(expected));
    mbuf_append(&mb, "\0", 1);
    ASSERT_STREQ(mb.buf, expected);
  }

  /*
   * Ping request injected in between of a fragmented message
   */
  mb.len = 0;
  s_ws_client1_connected = 0;
  ASSERT((nc = mg_connect(&mgr, local_addr, cb_ws_client1)) != NULL);
  mg_set_protocol_http_websocket(nc);
  nc->user_data = &mb;
  mg_send_websocket_handshake(nc, "/ws", NULL);
  poll_until(&mgr, 1, c_int_ne, &s_ws_client1_connected, (void *) 1);
  ASSERT_EQ(s_ws_client1_connected, 1);

  mg_send_websocket_frame(nc, WEBSOCKET_OP_TEXT | WEBSOCKET_DONT_FIN, "abc", 3);
  mg_send_websocket_frame(nc, WEBSOCKET_OP_CONTINUE | WEBSOCKET_DONT_FIN, "def",
                          3);

  mg_send_websocket_frame(nc, WEBSOCKET_OP_PING, "0123", 4);

  mg_send_websocket_frame(nc, WEBSOCKET_OP_CONTINUE, "ghi", 3);

  {
    /*
     * As a response to Ping, we should first receive Pong (0x8a),
     * and then text message (0x81) with our Ping (0x89) echo.
     * And then, our fragmented text message: abcdefghi.
     */
    const char *expected =
        "CONTROL:8a:[0123]81:[CONTROL:89:{0123}]81:[81:{abcdefghi}]";
    poll_until(&mgr, 1, c_int_eq, &mb.len, (void *) strlen(expected));
    mbuf_append(&mb, "\0", 1);
    ASSERT_STREQ(mb.buf, expected);
  }

  /*
   * Test illegal text frame in the middle of a fragmented message
   */
  mb.len = 0;
  s_ws_client1_connected = 0;
  ASSERT((nc = mg_connect(&mgr, local_addr, cb_ws_client1)) != NULL);
  mg_set_protocol_http_websocket(nc);
  nc->user_data = &mb;
  mg_send_websocket_handshake(nc, "/ws", NULL);
  poll_until(&mgr, 1, c_int_ne, &s_ws_client1_connected, (void *) 1);
  ASSERT_EQ(s_ws_client1_connected, 1);

  /* Send a few parts of a fragmented message */
  mg_send_websocket_frame(nc, WEBSOCKET_OP_TEXT | WEBSOCKET_DONT_FIN, "abc", 3);
  mg_send_websocket_frame(nc, WEBSOCKET_OP_CONTINUE | WEBSOCKET_DONT_FIN, "def",
                          3);

  /* Send (illegal) text frame in the middle of a fragmented message */
  mg_send_websocket_frame(nc, WEBSOCKET_OP_TEXT, "ghi", 3);

  /* Wait until connection is closed by the server */
  poll_until(&mgr, 1, c_int_ne, &s_ws_client1_connected, (void *) 0);
  ASSERT_EQ(s_ws_client1_connected, 0);

  /* Verify the error message */
  mbuf_append(&mb, "\0", 1);
  ASSERT_STREQ(
      mb.buf,
      "CONTROL:88:[non-continuation in the middle of a fragmented message]");

  /*
   * Test closing by the client
   */
  mb.len = 0;
  s_ws_client1_connected = 0;
  ASSERT((nc = mg_connect(&mgr, local_addr, cb_ws_client1)) != NULL);
  mg_set_protocol_http_websocket(nc);
  nc->user_data = &mb;
  mg_send_websocket_handshake(nc, "/ws", NULL);
  poll_until(&mgr, 1, c_int_ne, &s_ws_client1_connected, (void *) 1);
  ASSERT_EQ(s_ws_client1_connected, 1);

  /* Send a few parts of a fragmented message */
  mg_send_websocket_frame(nc, WEBSOCKET_OP_CLOSE, "bye", 3);

  /* Wait until connection is closed by the server */
  poll_until(&mgr, 1, c_int_ne, &s_ws_client1_connected, (void *) 0);
  ASSERT_EQ(s_ws_client1_connected, 0);
  /*
   * TODO(dfrank): mongoose closes the connection automatically when
   * mg_send_websocket_frame() is called with a WEBSOCKET_OP_CLOSE op, so we
   * can't hear anything from the server. Server is actually obliged to send
   * the control frame in response, but we can't test it here.
   */

  mg_mgr_free(&mgr);
  mbuf_free(&mb);

  return NULL;
}