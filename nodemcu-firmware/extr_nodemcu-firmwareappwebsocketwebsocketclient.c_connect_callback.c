#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int connectionState; scalar_t__ isSecure; int /*<<< orphan*/  port; int /*<<< orphan*/  hostname; int /*<<< orphan*/  path; TYPE_2__ const* extraHeaders; int /*<<< orphan*/  expectedSecKey; } ;
typedef  TYPE_1__ ws_info ;
typedef  int /*<<< orphan*/  uint8_t ;
struct espconn {scalar_t__ reverse; } ;
struct TYPE_10__ {char* member_0; char* member_1; } ;
typedef  TYPE_2__ const header_t ;

/* Variables and functions */
 TYPE_2__ const* DEFAULT_HEADERS ; 
 TYPE_2__ const* EMPTY_HEADERS ; 
 int /*<<< orphan*/  NODE_DBG (char*,...) ; 
 int /*<<< orphan*/  WS_INIT_REQUEST ; 
 scalar_t__ WS_INIT_REQUEST_LENGTH ; 
 int /*<<< orphan*/  espconn_regist_recvcb (struct espconn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  espconn_secure_send (struct espconn*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  espconn_send (struct espconn*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  generateSecKeys (char**,int /*<<< orphan*/ *) ; 
 scalar_t__ headers_length (TYPE_2__ const*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int os_sprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* sprintf_headers (char*,TYPE_2__ const*,TYPE_2__ const*,TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ws_initReceiveCallback ; 

__attribute__((used)) static void connect_callback(void *arg) {
  NODE_DBG("Connected\n");
  struct espconn *conn = (struct espconn *) arg;
  ws_info *ws = (ws_info *) conn->reverse;
  ws->connectionState = 3;

  espconn_regist_recvcb(conn, ws_initReceiveCallback);

  char *key;
  generateSecKeys(&key, &ws->expectedSecKey);

  header_t headers[] = {
	  {"Upgrade", "websocket"},
	  {"Connection", "Upgrade"},
	  {"Sec-WebSocket-Key", key},
	  {"Sec-WebSocket-Version", "13"},
	  {0}
  };

  const header_t *extraHeaders = ws->extraHeaders ? ws->extraHeaders : EMPTY_HEADERS;

  char buf[WS_INIT_REQUEST_LENGTH + strlen(ws->path) + strlen(ws->hostname) +
	  headers_length(DEFAULT_HEADERS) + headers_length(headers) + headers_length(extraHeaders) + 2];

  int len = os_sprintf(
                  buf,
                  WS_INIT_REQUEST,
                  ws->path,
                  ws->hostname,
                  ws->port
		  );

  len = sprintf_headers(buf + len, headers, extraHeaders, DEFAULT_HEADERS, 0) - buf;

  os_free(key);
  NODE_DBG("request: %s", buf);
  if (ws->isSecure)
    espconn_secure_send(conn, (uint8_t *) buf, len);
  else
    espconn_send(conn, (uint8_t *) buf, len);
}