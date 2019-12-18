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
typedef  int /*<<< orphan*/  Timestamp ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_VALID_TIMESTAMP (int /*<<< orphan*/ ) ; 
 scalar_t__ TIMESTAMP_IS_NOBEGIN (int /*<<< orphan*/ ) ; 
 scalar_t__ TIMESTAMP_IS_NOEND (int /*<<< orphan*/ ) ; 
 int timestamp_cmp_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmpTimestampWithOverflow(Timestamp ts1, int overflow1, Timestamp ts2)
{
	/*
	 * All the timestamps we deal with in jsonpath are produced by
	 * to_datetime() method.  So, they should be valid.
	 */
	Assert(IS_VALID_TIMESTAMP(ts2));

	/*
	 * Timestamp, which exceed lower (upper) bound, is always lower (higher)
	 * than any valid timestamp except minus (plus) infinity.
	 */
	if (overflow1)
	{
		if (overflow1 < 0)
		{
			if (TIMESTAMP_IS_NOBEGIN(ts2))
				return 1;
			else
				return -1;
		}
		if (overflow1 > 0)
		{
			if (TIMESTAMP_IS_NOEND(ts2))
				return -1;
			else
				return 1;
		}
	}

	return timestamp_cmp_internal(ts1, ts2);
}