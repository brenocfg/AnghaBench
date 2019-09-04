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
typedef  int ULONG_PTR ;
typedef  int DWORD ;

/* Variables and functions */

DWORD num_logical_cores(ULONG_PTR mask)
{
	DWORD     left_shift    = sizeof(ULONG_PTR) * 8 - 1;
	DWORD     bit_set_count = 0;
	ULONG_PTR bit_test      = (ULONG_PTR)1 << left_shift;

	for (DWORD i = 0; i <= left_shift; ++i) {
		bit_set_count += ((mask & bit_test) ? 1 : 0);
		bit_test      /= 2;
	}

	return bit_set_count;
}