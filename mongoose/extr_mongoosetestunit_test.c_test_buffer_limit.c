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
struct mg_connection {int recv_mbuf_limit; void* handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_EQ (int,int) ; 
 int /*<<< orphan*/  c_int_eq ; 
 int /*<<< orphan*/  ehb_srv ; 
 void* ehb_srv2 ; 
 struct mg_connection* mg_bind (struct mg_mgr*,char const*,int /*<<< orphan*/ ) ; 
 struct mg_connection* mg_connect (struct mg_mgr*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int*) ; 
 int /*<<< orphan*/  mg_printf (struct mg_connection*,char*) ; 
 int /*<<< orphan*/  mg_set_protocol_mqtt (struct mg_connection*) ; 
 int /*<<< orphan*/  poll_until (struct mg_mgr*,int,int /*<<< orphan*/ ,int*,void*) ; 

__attribute__((used)) static const char *test_buffer_limit(void) {
  struct mg_mgr mgr;
  struct mg_connection *clnt, *srv;
  const char *address = "tcp://127.0.0.1:7878";
  int res = 0;

  mg_mgr_init(&mgr, &res);
  ASSERT((srv = mg_bind(&mgr, address, ehb_srv)) != NULL);
  srv->recv_mbuf_limit = 1;
  ASSERT((clnt = mg_connect(&mgr, address, NULL)) != NULL);
  mg_printf(clnt, "abcd");

  poll_until(&mgr, 1, c_int_eq, &res, (void *) 4);

  /* expect four single byte read events */
  ASSERT_EQ(res, 4);

  /*
   * Make sure we're not closing full non-drained connections without any
   * protocol handler
   */
  res = 0;
  srv->handler = ehb_srv2;
  ASSERT((clnt = mg_connect(&mgr, address, NULL)) != NULL);
  mg_printf(clnt, "abcd");
  poll_until(&mgr, 1, c_int_eq, &res, (void *) 1);
  ASSERT_EQ(res, 0);

  /*
   * Make sure we're closing full non-drained connections with mqtt protocol
   * handler
   */
  res = 0;
  srv->handler = ehb_srv2;
  mg_set_protocol_mqtt(srv);
  ASSERT((clnt = mg_connect(&mgr, address, NULL)) != NULL);
  mg_printf(clnt, "abcd");
  poll_until(&mgr, 1, c_int_eq, &res, (void *) 1);
  ASSERT_EQ(res, 1);

  mg_mgr_free(&mgr);
  return NULL;
}