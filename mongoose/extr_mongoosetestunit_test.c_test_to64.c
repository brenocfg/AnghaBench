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

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EQ (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  to64 (char*) ; 

__attribute__((used)) static const char *test_to64(void) {
  ASSERT_EQ(to64("0"), 0);
  ASSERT_EQ(to64(""), 0);
  ASSERT_EQ(to64("123"), 123);
  ASSERT_EQ(to64("-34"), -34);
  ASSERT_EQ(to64("3566626116"), 3566626116U);
  return NULL;
}