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
struct net_device {int dummy; } ;

/* Variables and functions */
 int _rtl92e_calculate_bit_shift (int) ; 
 int rtl92e_readl (struct net_device*,int) ; 

u32 rtl92e_get_bb_reg(struct net_device *dev, u32 dwRegAddr, u32 dwBitMask)
{
	u32 OriginalValue, BitShift;

	OriginalValue = rtl92e_readl(dev, dwRegAddr);
	BitShift = _rtl92e_calculate_bit_shift(dwBitMask);

	return (OriginalValue & dwBitMask) >> BitShift;
}