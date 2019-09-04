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
struct mg_str {char* p; void* len; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT_EQ (scalar_t__,int) ; 
 int /*<<< orphan*/  ASSERT_STREQ (char*,char*) ; 
 scalar_t__ mg_get_http_var (struct mg_str*,char*,char*,int) ; 
 void* strlen (char*) ; 

__attribute__((used)) static const char *test_get_http_var(void) {
  char buf[256];
  struct mg_str body;
  body.p = "key1=value1&key2=value2&key3=value%203&key4=value+4";
  body.len = strlen(body.p);

  ASSERT(mg_get_http_var(&body, "key1", buf, sizeof(buf)) > 0);
  ASSERT_STREQ(buf, "value1");
  ASSERT(mg_get_http_var(&body, "KEY1", buf, sizeof(buf)) > 0);
  ASSERT_STREQ(buf, "value1");
  ASSERT(mg_get_http_var(&body, "key2", buf, sizeof(buf)) > 0);
  ASSERT_STREQ(buf, "value2");
  ASSERT(mg_get_http_var(&body, "key3", buf, sizeof(buf)) > 0);
  ASSERT_STREQ(buf, "value 3");
  ASSERT(mg_get_http_var(&body, "key4", buf, sizeof(buf)) > 0);
  ASSERT_STREQ(buf, "value 4");

  ASSERT_EQ(mg_get_http_var(&body, "key1", NULL, sizeof(buf)), -2);
  ASSERT_EQ(mg_get_http_var(&body, "key1", buf, 0), -2);
  ASSERT_EQ(mg_get_http_var(&body, NULL, buf, sizeof(buf)), -1);
  ASSERT_EQ(mg_get_http_var(&body, "key1", buf, 1), -3);

  body.p = "key=broken%2";
  body.len = strlen(body.p);
  ASSERT(mg_get_http_var(&body, "key", buf, sizeof(buf)) < 0);

  body.p = "key=broken%2x";
  body.len = strlen(body.p);
  ASSERT(mg_get_http_var(&body, "key", buf, sizeof(buf)) < 0);

  ASSERT_EQ(mg_get_http_var(&body, "inexistent", buf, sizeof(buf)), -4);

  return NULL;
}