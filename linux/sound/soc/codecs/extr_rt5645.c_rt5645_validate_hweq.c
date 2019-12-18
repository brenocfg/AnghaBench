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
 unsigned short RT5645_EQ_CTRL2 ; 

__attribute__((used)) static bool rt5645_validate_hweq(unsigned short reg)
{
	if ((reg >= 0x1a4 && reg <= 0x1cd) | (reg >= 0x1e5 && reg <= 0x1f8) |
		(reg == RT5645_EQ_CTRL2))
		return true;

	return false;
}