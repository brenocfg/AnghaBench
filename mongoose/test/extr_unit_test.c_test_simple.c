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
struct simple_data {int /*<<< orphan*/  num_close; int /*<<< orphan*/  num_send; int /*<<< orphan*/  num_recv; int /*<<< orphan*/  num_connect; int /*<<< orphan*/  num_accept; int /*<<< orphan*/  fail; int /*<<< orphan*/  data_rcvd; int /*<<< orphan*/  to_send; struct mg_connection* sclient_nc; struct simple_data* sclient_data; } ;
struct mg_mgr {int dummy; } ;
struct mg_connection {struct simple_data* user_data; } ;
typedef  int /*<<< orphan*/  server_data ;
typedef  int /*<<< orphan*/  sclient_data ;
typedef  int /*<<< orphan*/  client_data ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_EQ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ASSERT_STREQ (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cb_client ; 
 int /*<<< orphan*/  cb_server ; 
 int /*<<< orphan*/  memset (struct simple_data*,int /*<<< orphan*/ ,int) ; 
 struct mg_connection* mg_bind (struct mg_mgr*,char const*,int /*<<< orphan*/ ) ; 
 struct mg_connection* mg_connect (struct mg_mgr*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_poll (struct mg_mgr*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static const char *test_simple(void) {
  struct mg_mgr mgr;
  struct mg_connection *nc_server, *nc_client, *nc_sclient;
  const char *address = "tcp://127.0.0.1:8910";
  struct simple_data client_data, server_data, sclient_data;

  (void) nc_sclient;
  mg_mgr_init(&mgr, NULL);

  ASSERT((nc_server = mg_bind(&mgr, address, cb_server)) != NULL);
  nc_server->user_data = &server_data;
  memset(&server_data, 0, sizeof(server_data));
  server_data.sclient_data = &sclient_data;
  memset(&sclient_data, 0, sizeof(sclient_data));

  mg_mgr_poll(&mgr, 1); /* 1 - nothing */

  ASSERT((nc_client = mg_connect(&mgr, address, cb_client)) != NULL);
  nc_client->user_data = &client_data;
  memset(&client_data, 0, sizeof(client_data));
  strcpy(client_data.to_send, "hi");

  mg_mgr_poll(&mgr, 1); /* 2 - client connects and sends, server accepts */
  ASSERT_EQ(server_data.num_accept, 0);
  ASSERT_EQ(sclient_data.num_accept, 1);
  ASSERT_EQ(client_data.num_connect, 1);
  ASSERT_EQ(client_data.num_send, 1);
  ASSERT_STREQ(client_data.fail, "");
  ASSERT_STREQ(server_data.fail, "");

  ASSERT(server_data.sclient_nc != NULL);
  nc_sclient = server_data.sclient_nc;
  ASSERT_EQ(sclient_data.num_send, 0);
  ASSERT_EQ(sclient_data.num_recv, 0);

  strcpy(sclient_data.to_send, "hello");
  mg_mgr_poll(&mgr, 1); /* 3 - server receives, buffers response, closes */
  ASSERT_STREQ(sclient_data.fail, "");
  ASSERT_EQ(sclient_data.num_recv, 1);
  ASSERT_EQ(sclient_data.num_send, 0);
  ASSERT_EQ(client_data.num_recv, 0);
  ASSERT_STREQ(sclient_data.data_rcvd, "hi");

  mg_mgr_poll(&mgr, 1); /* 4 - server sends */
  ASSERT_STREQ(sclient_data.fail, "");
  ASSERT_EQ(sclient_data.num_send, 1);

  mg_mgr_poll(&mgr, 1); /* 5 - client receives */
  ASSERT_STREQ(client_data.fail, "");
  ASSERT_EQ(client_data.num_recv, 1);
  ASSERT_STREQ(client_data.data_rcvd, "hello");

  mg_mgr_free(&mgr);

  ASSERT_STREQ(client_data.fail, "");
  ASSERT_STREQ(server_data.fail, "");
  ASSERT_STREQ(sclient_data.fail, "");

  ASSERT_EQ(server_data.num_accept, 0);
  ASSERT_EQ(server_data.num_connect, 0);
  ASSERT_EQ(server_data.num_recv, 0);
  ASSERT_EQ(server_data.num_send, 0);
  ASSERT_EQ(server_data.num_close, 1);

  ASSERT_EQ(client_data.num_accept, 0);
  ASSERT_EQ(client_data.num_connect, 1);
  ASSERT_EQ(client_data.num_recv, 1);
  ASSERT_EQ(client_data.num_send, 1);
  ASSERT_EQ(client_data.num_close, 1);

  ASSERT_EQ(sclient_data.num_accept, 1);
  ASSERT_EQ(sclient_data.num_connect, 0);
  ASSERT_EQ(sclient_data.num_recv, 1);
  ASSERT_EQ(sclient_data.num_send, 1);
  ASSERT_EQ(sclient_data.num_close, 1);

  return NULL;
}