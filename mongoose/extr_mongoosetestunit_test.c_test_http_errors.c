#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mg_mgr {int dummy; } ;
struct mg_connection {char* user_data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * enable_directory_listing; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_STREQ_NZ (char*,char*) ; 
 int /*<<< orphan*/  c_str_ne ; 
 int /*<<< orphan*/  cb1 ; 
 int /*<<< orphan*/  cb8 ; 
 struct mg_connection* mg_bind (struct mg_mgr*,char const*,int /*<<< orphan*/ ) ; 
 struct mg_connection* mg_connect (struct mg_mgr*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_printf (struct mg_connection*,char*,char*) ; 
 int /*<<< orphan*/  mg_set_protocol_http_websocket (struct mg_connection*) ; 
 int /*<<< orphan*/  poll_until (struct mg_mgr*,int,int /*<<< orphan*/ ,char*,void*) ; 
 TYPE_1__ s_http_server_opts ; 
 int /*<<< orphan*/  system (char*) ; 

__attribute__((used)) static const char *test_http_errors(void) {
  struct mg_mgr mgr;
  struct mg_connection *nc;
  const char *local_addr = "127.0.0.1:7777";
  char status[1000] = "";

  mg_mgr_init(&mgr, NULL);
  s_http_server_opts.enable_directory_listing = NULL;
  ASSERT((nc = mg_bind(&mgr, local_addr, cb1)) != NULL);
  mg_set_protocol_http_websocket(nc);

#if !defined(TEST_UNDER_VIRTUALBOX) && !defined(_WIN32)
  /* Test file which exists but cannot be opened */
  ASSERT((nc = mg_connect(&mgr, local_addr, cb8)) != NULL);
  mg_set_protocol_http_websocket(nc);
  nc->user_data = status;
  system("touch test_unreadable; chmod 000 test_unreadable");
  mg_printf(nc, "GET /%s HTTP/1.0\n\n", "../test_unreadable");

  /* Run event loop. Use more cycles to let file download complete. */
  poll_until(&mgr, 1, c_str_ne, status, (void *) "");
  system("rm -f test_unreadable");

  /* Check that it failed */
  ASSERT_STREQ_NZ(status, "HTTP/1.1 403");
#endif

  /* Test non existing file */
  ASSERT((nc = mg_connect(&mgr, local_addr, cb8)) != NULL);
  mg_set_protocol_http_websocket(nc);
  status[0] = '\0';
  nc->user_data = status;
  mg_printf(nc, "GET /%s HTTP/1.0\n\n", "/please_dont_create_this_file_srsly");

  poll_until(&mgr, 1, c_str_ne, status, (void *) "");

  /* Check that it failed */
  ASSERT_STREQ_NZ(status, "HTTP/1.1 404");

  /* Cleanup */
  mg_mgr_free(&mgr);

  return NULL;
}