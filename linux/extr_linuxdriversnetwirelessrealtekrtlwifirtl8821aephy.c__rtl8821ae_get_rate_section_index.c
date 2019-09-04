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
typedef  scalar_t__ u8 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 

__attribute__((used)) static u8 _rtl8821ae_get_rate_section_index(u32 regaddr)
{
	u8 index = 0;
	regaddr &= 0xFFF;
	if (regaddr >= 0xC20 && regaddr <= 0xC4C)
		index = (u8)((regaddr - 0xC20) / 4);
	else if (regaddr >= 0xE20 && regaddr <= 0xE4C)
		index = (u8)((regaddr - 0xE20) / 4);
	else
		WARN_ONCE(true,
			  "rtl8821ae: Invalid RegAddr 0x%x\n", regaddr);
	return index;
}