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
struct mg_connection {char* user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_STREQ (char*,char*) ; 
 int /*<<< orphan*/  c_str_ne ; 
 int /*<<< orphan*/  cb3 ; 
 int /*<<< orphan*/  cb4 ; 
 struct mg_connection* mg_bind (struct mg_mgr*,char*,int /*<<< orphan*/ ) ; 
 struct mg_connection* mg_connect_ws (struct mg_mgr*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_set_protocol_http_websocket (struct mg_connection*) ; 
 int /*<<< orphan*/  poll_until (struct mg_mgr*,int,int /*<<< orphan*/ ,char*,void*) ; 

__attribute__((used)) static const char *test_connect_ws(void) {
  struct mg_mgr mgr;
  struct mg_connection *nc;
  const char *urls[] = {"ws://127.0.0.1:7778/ws", "http://127.0.0.1:7778/ws",
                        "127.0.0.1:7778/ws", NULL};
  const char **url;

  mg_mgr_init(&mgr, NULL);
  /* mgr.hexdump_file = "-"; */
  ASSERT((nc = mg_bind(&mgr, "127.0.0.1:7778", cb3)) != NULL);
  mg_set_protocol_http_websocket(nc);

  for (url = urls; *url != NULL; url++) {
    char buf[20] = "";
    ASSERT((nc = mg_connect_ws(&mgr, cb4, "ws://127.0.0.1:7778/ws", NULL,
                               NULL)) != NULL);
    nc->user_data = buf;
    poll_until(&mgr, 1, c_str_ne, buf, (void *) "");
    ASSERT_STREQ(buf, "A");
  }

  mg_mgr_free(&mgr);

  return NULL;
}