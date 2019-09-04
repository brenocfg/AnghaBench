#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  len; } ;
struct udp_res {TYPE_1__ buf_clnt; TYPE_1__ buf_srv; } ;
struct mg_mgr {int dummy; } ;
struct mg_connection {int dummy; } ;
typedef  int /*<<< orphan*/  res ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_STREQ_NZ (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  c_int_eq ; 
 int /*<<< orphan*/  eh3_clnt ; 
 int /*<<< orphan*/  eh3_srv ; 
 int /*<<< orphan*/  mbuf_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mbuf_init (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (struct udp_res*,int /*<<< orphan*/ ,int) ; 
 struct mg_connection* mg_bind (struct mg_mgr*,char const*,int /*<<< orphan*/ ) ; 
 struct mg_connection* mg_connect (struct mg_mgr*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,struct udp_res*) ; 
 int /*<<< orphan*/  poll_until (struct mg_mgr*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static const char *test_udp(void) {
  struct mg_mgr mgr;
  struct mg_connection *nc1, *nc2;
  const char *address = "udp://127.0.0.1:7878";
  struct udp_res res;
  memset(&res, 0, sizeof(res));
  mbuf_init(&res.buf_srv, 100);
  mbuf_init(&res.buf_clnt, 100);

  mg_mgr_init(&mgr, &res);
  ASSERT((nc1 = mg_bind(&mgr, address, eh3_srv)) != NULL);
  ASSERT((nc2 = mg_connect(&mgr, address, eh3_clnt)) != NULL);

  poll_until(&mgr, 1, c_int_eq, &res.buf_clnt.len, (void *) 23);
  ASSERT_STREQ_NZ(res.buf_srv.buf, "ACCEPT+ RECV boo! CLOSE");
  ASSERT_STREQ_NZ(res.buf_clnt.buf, "CONNECT RECV boo! CLOSE");

  mbuf_free(&res.buf_srv);
  mbuf_free(&res.buf_clnt);
  mg_mgr_free(&mgr);

  return NULL;
}