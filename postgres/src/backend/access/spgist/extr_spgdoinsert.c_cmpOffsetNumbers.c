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
typedef  scalar_t__ OffsetNumber ;

/* Variables and functions */

__attribute__((used)) static int
cmpOffsetNumbers(const void *a, const void *b)
{
	if (*(const OffsetNumber *) a == *(const OffsetNumber *) b)
		return 0;
	return (*(const OffsetNumber *) a > *(const OffsetNumber *) b) ? 1 : -1;
}