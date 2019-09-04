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
 int /*<<< orphan*/  ASSERT_EQ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ASSERT_STREQ (char*,char*) ; 
 int /*<<< orphan*/  avt (char**,int,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static const char *test_alloc_vprintf(void) {
  char buf[5], *p = buf;

  ASSERT_EQ(avt(&p, sizeof(buf), "%d", 123), 3);
  ASSERT(p == buf);
  ASSERT_STREQ(p, "123");

  ASSERT_EQ(avt(&p, sizeof(buf), "%d", 123456789), 9);
  ASSERT(p != buf);
  ASSERT_STREQ(p, "123456789");
  free(p);

  return NULL;
}