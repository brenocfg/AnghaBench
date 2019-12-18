#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mg_mgr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; } ;
struct mg_connection {int /*<<< orphan*/ * proto_data; int /*<<< orphan*/  (* proto_data_destructor ) (int /*<<< orphan*/ *) ;TYPE_2__ message; TYPE_1__ body; int /*<<< orphan*/  handler; int /*<<< orphan*/  sock; struct mg_mgr* mgr; } ;
struct http_message {int /*<<< orphan*/ * proto_data; int /*<<< orphan*/  (* proto_data_destructor ) (int /*<<< orphan*/ *) ;TYPE_2__ message; TYPE_1__ body; int /*<<< orphan*/  handler; int /*<<< orphan*/  sock; struct mg_mgr* mgr; } ;
typedef  int /*<<< orphan*/  nc ;
typedef  int /*<<< orphan*/  hm ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_EQ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ASSERT_EQ64 (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ASSERT_STREQ (char*,char*) ; 
 int /*<<< orphan*/  INVALID_SOCKET ; 
 int /*<<< orphan*/  eh_chunk2 ; 
 int /*<<< orphan*/  memset (struct mg_connection*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mg_handle_chunked (struct mg_connection*,struct mg_connection*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_http_create_proto_data (struct mg_connection*) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 char* s_events ; 
 int s_handle_chunk_event ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *test_http_chunk2(void) {
  struct mg_connection nc;
  struct http_message hm;
  char buf[100] = "5\r\nhe";
  struct mg_mgr mgr;
  mg_mgr_init(&mgr, NULL);

  memset(&nc, 0, sizeof(nc));
  memset(&hm, 0, sizeof(hm));
  nc.mgr = &mgr;
  nc.sock = INVALID_SOCKET;
  nc.handler = eh_chunk2;
  mg_http_create_proto_data(&nc);
  hm.message.len = hm.body.len = ~0;

  s_handle_chunk_event = 0;
  ASSERT_EQ(mg_handle_chunked(&nc, &hm, buf, strlen(buf)), 0);

  /* Simulate arrival of chunks. MG_EV_HTTP_CHUNK events are not handled. */
  strcat(buf, "llo\r");
  ASSERT_EQ(mg_handle_chunked(&nc, &hm, buf, strlen(buf)), 0);
  ASSERT_STREQ(buf, "5\r\nhello\r");

  strcat(buf, "\n");
  ASSERT_EQ(mg_handle_chunked(&nc, &hm, buf, strlen(buf)), 5);
  ASSERT_STREQ(buf, "hello");

  s_handle_chunk_event = 1;
  strcat(buf, "3\r\n:-)\r\n");
  ASSERT_EQ(mg_handle_chunked(&nc, &hm, buf, strlen(buf)), 8);
  ASSERT_STREQ(buf, "");

  s_handle_chunk_event = 0;
  strcat(buf, "3\r\n...\r\na\r\n0123456789\r\n0\r");
  ASSERT_EQ(mg_handle_chunked(&nc, &hm, buf, strlen(buf)), 13);
  ASSERT_STREQ(buf, "...01234567890\r");
  ASSERT_EQ64(hm.message.len, (size_t) ~0);

  strcat(buf, "\n\r\n");
  ASSERT_EQ(mg_handle_chunked(&nc, &hm, buf, strlen(buf)), 13);
  ASSERT_STREQ(buf, "...0123456789");
  ASSERT_EQ(hm.message.len, 13);

  ASSERT_STREQ(s_events, "_102_102_102_102");

  ASSERT(nc.proto_data != NULL);
  nc.proto_data_destructor(nc.proto_data);

  mg_mgr_free(&mgr);

  return NULL;
}