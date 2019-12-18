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
typedef  int uint64 ;
typedef  int /*<<< orphan*/  pg_atomic_uint64 ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EXPECT_EQ_U64 (int,int) ; 
 int /*<<< orphan*/  EXPECT_TRUE (int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int pg_atomic_add_fetch_u64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pg_atomic_compare_exchange_u64 (int /*<<< orphan*/ *,int*,int) ; 
 int pg_atomic_exchange_u64 (int /*<<< orphan*/ *,int) ; 
 int pg_atomic_fetch_add_u64 (int /*<<< orphan*/ *,int) ; 
 int pg_atomic_fetch_and_u64 (int /*<<< orphan*/ *,int) ; 
 int pg_atomic_fetch_or_u64 (int /*<<< orphan*/ *,int) ; 
 int pg_atomic_fetch_sub_u64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pg_atomic_init_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pg_atomic_read_u64 (int /*<<< orphan*/ *) ; 
 int pg_atomic_sub_fetch_u64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pg_atomic_write_u64 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
test_atomic_uint64(void)
{
	pg_atomic_uint64 var;
	uint64		expected;
	int			i;

	pg_atomic_init_u64(&var, 0);
	EXPECT_EQ_U64(pg_atomic_read_u64(&var), 0);
	pg_atomic_write_u64(&var, 3);
	EXPECT_EQ_U64(pg_atomic_read_u64(&var), 3);
	EXPECT_EQ_U64(pg_atomic_fetch_add_u64(&var, pg_atomic_read_u64(&var) - 2),
				  3);
	EXPECT_EQ_U64(pg_atomic_fetch_sub_u64(&var, 1), 4);
	EXPECT_EQ_U64(pg_atomic_sub_fetch_u64(&var, 3), 0);
	EXPECT_EQ_U64(pg_atomic_add_fetch_u64(&var, 10), 10);
	EXPECT_EQ_U64(pg_atomic_exchange_u64(&var, 5), 10);
	EXPECT_EQ_U64(pg_atomic_exchange_u64(&var, 0), 5);

	/* fail exchange because of old expected */
	expected = 10;
	EXPECT_TRUE(!pg_atomic_compare_exchange_u64(&var, &expected, 1));

	/* CAS is allowed to fail due to interrupts, try a couple of times */
	for (i = 0; i < 100; i++)
	{
		expected = 0;
		if (!pg_atomic_compare_exchange_u64(&var, &expected, 1))
			break;
	}
	if (i == 100)
		elog(ERROR, "atomic_compare_exchange_u64() never succeeded");
	EXPECT_EQ_U64(pg_atomic_read_u64(&var), 1);

	pg_atomic_write_u64(&var, 0);

	/* try setting flagbits */
	EXPECT_TRUE(!(pg_atomic_fetch_or_u64(&var, 1) & 1));
	EXPECT_TRUE(pg_atomic_fetch_or_u64(&var, 2) & 1);
	EXPECT_EQ_U64(pg_atomic_read_u64(&var), 3);
	/* try clearing flagbits */
	EXPECT_EQ_U64((pg_atomic_fetch_and_u64(&var, ~2) & 3), 3);
	EXPECT_EQ_U64(pg_atomic_fetch_and_u64(&var, ~1), 1);
	/* no bits set anymore */
	EXPECT_EQ_U64(pg_atomic_fetch_and_u64(&var, ~0), 0);
}