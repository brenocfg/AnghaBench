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
struct TYPE_2__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  len; } ;
struct mg_connection {TYPE_1__ send_mbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EQ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_test_connection (struct mg_connection*) ; 
 int /*<<< orphan*/  mbuf_free (TYPE_1__*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mg_printf_http_chunk (struct mg_connection*,char*,int,char*) ; 
 int /*<<< orphan*/  mg_send_http_chunk (struct mg_connection*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *test_http_chunk(void) {
  struct mg_connection nc;
  init_test_connection(&nc);

  mg_printf_http_chunk(&nc, "%d %s", 123, ":-)");
  ASSERT_EQ(nc.send_mbuf.len, 12);
  ASSERT_EQ(memcmp(nc.send_mbuf.buf, "7\r\n123 :-)\r\n", 12), 0);
  mbuf_free(&nc.send_mbuf);

  mg_send_http_chunk(&nc, "", 0);
  ASSERT_EQ(nc.send_mbuf.len, 5);
  ASSERT_EQ(memcmp(nc.send_mbuf.buf, "0\r\n\r\n", 3), 0);
  mbuf_free(&nc.send_mbuf);

  return NULL;
}