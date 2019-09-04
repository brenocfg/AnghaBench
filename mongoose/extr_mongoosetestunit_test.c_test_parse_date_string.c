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
 int /*<<< orphan*/  ASSERT_EQ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mg_parse_date_string (char*) ; 

__attribute__((used)) static const char *test_parse_date_string(void) {
  ASSERT_EQ(mg_parse_date_string("Sat, 31 Oct 2019 10:51:12 GMT"), 1572519072);
  ASSERT_EQ(mg_parse_date_string("31/Oct/2019 10:51:12 GMT"), 1572519072);
  ASSERT_EQ(mg_parse_date_string("31 Oct 2019 10:51:12 GMT"), 1572519072);
  ASSERT_EQ(mg_parse_date_string("31-Oct-2019 10:51:12 GMT"), 1572519072);
  return NULL;
}