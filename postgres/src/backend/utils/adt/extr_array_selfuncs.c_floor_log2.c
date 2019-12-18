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
typedef  int uint32 ;

/* Variables and functions */

__attribute__((used)) static int
floor_log2(uint32 n)
{
	int			logval = 0;

	if (n == 0)
		return -1;
	if (n >= (1 << 16))
	{
		n >>= 16;
		logval += 16;
	}
	if (n >= (1 << 8))
	{
		n >>= 8;
		logval += 8;
	}
	if (n >= (1 << 4))
	{
		n >>= 4;
		logval += 4;
	}
	if (n >= (1 << 2))
	{
		n >>= 2;
		logval += 2;
	}
	if (n >= (1 << 1))
	{
		logval += 1;
	}
	return logval;
}