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
struct adapter {int dummy; } ;

/* Variables and functions */
 int bMaskDWord ; 
 int phy_CalculateBitShift (int) ; 
 int rtw_read32 (struct adapter*,int) ; 
 int /*<<< orphan*/  rtw_write32 (struct adapter*,int,int) ; 

void PHY_SetBBReg_8723B(
	struct adapter *Adapter,
	u32 RegAddr,
	u32 BitMask,
	u32 Data
)
{
	/* u16 BBWaitCounter	= 0; */
	u32 OriginalValue, BitShift;

#if (DISABLE_BB_RF == 1)
	return;
#endif

	/* RT_TRACE(COMP_RF, DBG_TRACE, ("--->PHY_SetBBReg(): RegAddr(%#lx), BitMask(%#lx), Data(%#lx)\n", RegAddr, BitMask, Data)); */

	if (BitMask != bMaskDWord) { /* if not "double word" write */
		OriginalValue = rtw_read32(Adapter, RegAddr);
		BitShift = phy_CalculateBitShift(BitMask);
		Data = ((OriginalValue & (~BitMask)) | ((Data << BitShift) & BitMask));
	}

	rtw_write32(Adapter, RegAddr, Data);

}