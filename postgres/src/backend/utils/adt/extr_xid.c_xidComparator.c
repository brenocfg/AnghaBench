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
typedef  scalar_t__ TransactionId ;

/* Variables and functions */

int
xidComparator(const void *arg1, const void *arg2)
{
	TransactionId xid1 = *(const TransactionId *) arg1;
	TransactionId xid2 = *(const TransactionId *) arg2;

	if (xid1 > xid2)
		return 1;
	if (xid1 < xid2)
		return -1;
	return 0;
}