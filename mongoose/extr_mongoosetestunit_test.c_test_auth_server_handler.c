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
typedef  int /*<<< orphan*/  user ;
struct mg_str {int dummy; } ;
struct mg_connection {scalar_t__ user_data; } ;
struct http_message {int dummy; } ;
typedef  int /*<<< orphan*/  pass ;

/* Variables and functions */
#define  MG_EV_HTTP_REQUEST 129 
#define  MG_EV_WEBSOCKET_HANDSHAKE_REQUEST 128 
 int mg_get_http_basic_auth (struct http_message*,char*,int,char*,int) ; 
 struct mg_str* mg_get_http_header (struct http_message*,char*) ; 
 int /*<<< orphan*/  mg_vcmp (struct mg_str*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void test_auth_server_handler(struct mg_connection *nc, int ev,
                                     void *ev_data) {
  struct http_message *hm = (struct http_message *) ev_data;
  struct mg_str *hdr;
  char user[256] = "";
  char pass[256] = "";
  int res;

  switch (ev) {
    case MG_EV_WEBSOCKET_HANDSHAKE_REQUEST:
    case MG_EV_HTTP_REQUEST: {
      hdr = mg_get_http_header(hm, "Sec-WebSocket-Protocol");
      if (hdr != NULL) {
        if (mg_vcmp(hdr, "myproto") == 0) {
          *(int *) nc->user_data = 2;
          break;
        }
      }

      res = mg_get_http_basic_auth(hm, user, sizeof(user), pass, sizeof(pass));
      if (res == -1) {
        *(int *) nc->user_data = -1;
        break;
      }

      if (strcmp(user, "foo") == 0 && strcmp(pass, "bar") == 0) {
        *(int *) nc->user_data = 1;
      } else {
        *(int *) nc->user_data = -2;
      }

      break;
    }
  }
}