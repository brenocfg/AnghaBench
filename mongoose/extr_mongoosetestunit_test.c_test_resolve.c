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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT_EQ (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_STREQ (char*,char*) ; 
 scalar_t__ mg_resolve (char*,char*,int) ; 

__attribute__((used)) static const char *test_resolve(void) {
  char buf[20];

  ASSERT(mg_resolve("localhost", buf, sizeof(buf)) > 0);
  ASSERT_STREQ(buf, "127.0.0.1");

  ASSERT_EQ(mg_resolve("please_dont_name_a_host_like_ths", buf, sizeof(buf)),
            0);
  return NULL;
}