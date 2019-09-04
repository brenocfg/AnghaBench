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
typedef  scalar_t__ u64 ;

/* Variables and functions */

__attribute__((used)) static int field_cmp(u64 field_a, u64 field_b)
{
	if (field_a > field_b)
		return 1;
	if (field_a < field_b)
		return -1;
	return 0;
}