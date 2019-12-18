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
typedef  scalar_t__ Size ;
typedef  int /*<<< orphan*/  BrinTuple ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,scalar_t__) ; 

bool
brin_tuples_equal(const BrinTuple *a, Size alen, const BrinTuple *b, Size blen)
{
	if (alen != blen)
		return false;
	if (memcmp(a, b, alen) != 0)
		return false;
	return true;
}