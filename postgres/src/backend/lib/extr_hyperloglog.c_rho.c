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
typedef  scalar_t__ uint8 ;
typedef  int uint32 ;

/* Variables and functions */

__attribute__((used)) static inline uint8
rho(uint32 x, uint8 b)
{
	uint8		j = 1;

	while (j <= b && !(x & 0x80000000))
	{
		j++;
		x <<= 1;
	}

	return j;
}