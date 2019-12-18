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
typedef  int int32 ;

/* Variables and functions */

__attribute__((used)) static int32
partition_hbound_cmp(int modulus1, int remainder1, int modulus2, int remainder2)
{
	if (modulus1 < modulus2)
		return -1;
	if (modulus1 > modulus2)
		return 1;
	if (modulus1 == modulus2 && remainder1 != remainder2)
		return (remainder1 > remainder2) ? 1 : -1;
	return 0;
}