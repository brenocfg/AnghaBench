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
 long my_log2 (long) ; 

__attribute__((used)) static long
next_pow2_long(long num)
{
	/* my_log2's internal range check is sufficient */
	return 1L << my_log2(num);
}