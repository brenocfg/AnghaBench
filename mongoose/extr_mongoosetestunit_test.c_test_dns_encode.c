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
struct TYPE_2__ {char* buf; char const len; } ;
struct mg_connection {TYPE_1__ send_mbuf; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  ASSERT_EQ (char const,int) ; 
 int /*<<< orphan*/  ASSERT_STREQ_NZ (char const*,char*) ; 
 int MG_DNS_AAAA_RECORD ; 
 int MG_DNS_A_RECORD ; 
 int /*<<< orphan*/  init_test_connection (struct mg_connection*) ; 
 int /*<<< orphan*/  mbuf_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mg_send_dns_query (struct mg_connection*,char*,int) ; 

__attribute__((used)) static const char *test_dns_encode(void) {
  struct mg_connection nc;
  const char *got;
  int query_types[] = {MG_DNS_A_RECORD, MG_DNS_AAAA_RECORD};
  size_t i;
  init_test_connection(&nc);

  /*
   * Testing TCP encoding since when the connection
   * is in UDP mode the data is not stored in the send buffer.
   */

  for (i = 0; i < ARRAY_SIZE(query_types); i++) {
    mg_send_dns_query(&nc, "www.cesanta.com", query_types[i]);
    got = nc.send_mbuf.buf;
    ASSERT_EQ(nc.send_mbuf.len, 12 + 4 + 13 + 4 + 2);
    ASSERT_EQ(got[14], 3);
    ASSERT_STREQ_NZ(&got[15], "www");
    ASSERT_EQ(got[18], 7);
    ASSERT_STREQ_NZ(&got[19], "cesanta");
    ASSERT_EQ(got[26], 3);
    ASSERT_STREQ_NZ(&got[27], "com");
    ASSERT_EQ(got[30], 0);
    ASSERT_EQ(got[31], 0);
    ASSERT_EQ(got[32], query_types[i]);
    ASSERT_EQ(got[33], 0);
    ASSERT_EQ(got[34], 1);

    mbuf_free(&nc.send_mbuf);
  }
  return NULL;
}