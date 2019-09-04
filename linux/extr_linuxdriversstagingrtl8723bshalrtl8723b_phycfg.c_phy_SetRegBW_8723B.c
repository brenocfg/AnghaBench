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
typedef  int u16 ;
struct adapter {int dummy; } ;
typedef  enum CHANNEL_WIDTH { ____Placeholder_CHANNEL_WIDTH } CHANNEL_WIDTH ;

/* Variables and functions */
 int BIT7 ; 
 int BIT8 ; 
#define  CHANNEL_WIDTH_20 130 
#define  CHANNEL_WIDTH_40 129 
#define  CHANNEL_WIDTH_80 128 
 int /*<<< orphan*/  DBG_871X (char*,int) ; 
 int /*<<< orphan*/  REG_TRXPTCL_CTL_8723B ; 
 int rtw_read16 (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write16 (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void phy_SetRegBW_8723B(
	struct adapter *Adapter, enum CHANNEL_WIDTH CurrentBW
)
{
	u16 RegRfMod_BW, u2tmp = 0;
	RegRfMod_BW = rtw_read16(Adapter, REG_TRXPTCL_CTL_8723B);

	switch (CurrentBW) {
	case CHANNEL_WIDTH_20:
		rtw_write16(Adapter, REG_TRXPTCL_CTL_8723B, (RegRfMod_BW & 0xFE7F)); /*  BIT 7 = 0, BIT 8 = 0 */
		break;

	case CHANNEL_WIDTH_40:
		u2tmp = RegRfMod_BW | BIT7;
		rtw_write16(Adapter, REG_TRXPTCL_CTL_8723B, (u2tmp & 0xFEFF)); /*  BIT 7 = 1, BIT 8 = 0 */
		break;

	case CHANNEL_WIDTH_80:
		u2tmp = RegRfMod_BW | BIT8;
		rtw_write16(Adapter, REG_TRXPTCL_CTL_8723B, (u2tmp & 0xFF7F)); /*  BIT 7 = 0, BIT 8 = 1 */
		break;

	default:
		DBG_871X("phy_PostSetBWMode8723B():	unknown Bandwidth: %#X\n", CurrentBW);
		break;
	}
}