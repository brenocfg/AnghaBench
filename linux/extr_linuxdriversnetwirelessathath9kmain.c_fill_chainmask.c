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
typedef  int u32 ;

/* Variables and functions */
 int BIT (int) ; 

__attribute__((used)) static u32 fill_chainmask(u32 cap, u32 new)
{
	u32 filled = 0;
	int i;

	for (i = 0; cap && new; i++, cap >>= 1) {
		if (!(cap & BIT(0)))
			continue;

		if (new & BIT(0))
			filled |= BIT(i);

		new >>= 1;
	}

	return filled;
}