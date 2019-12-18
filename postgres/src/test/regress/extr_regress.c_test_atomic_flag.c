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
typedef  int /*<<< orphan*/  pg_atomic_flag ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT_TRUE (int) ; 
 int /*<<< orphan*/  pg_atomic_clear_flag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_atomic_init_flag (int /*<<< orphan*/ *) ; 
 int pg_atomic_test_set_flag (int /*<<< orphan*/ *) ; 
 int pg_atomic_unlocked_test_flag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
test_atomic_flag(void)
{
	pg_atomic_flag flag;

	pg_atomic_init_flag(&flag);
	EXPECT_TRUE(pg_atomic_unlocked_test_flag(&flag));
	EXPECT_TRUE(pg_atomic_test_set_flag(&flag));
	EXPECT_TRUE(!pg_atomic_unlocked_test_flag(&flag));
	EXPECT_TRUE(!pg_atomic_test_set_flag(&flag));
	pg_atomic_clear_flag(&flag);
	EXPECT_TRUE(pg_atomic_unlocked_test_flag(&flag));
	EXPECT_TRUE(pg_atomic_test_set_flag(&flag));
	pg_atomic_clear_flag(&flag);
}