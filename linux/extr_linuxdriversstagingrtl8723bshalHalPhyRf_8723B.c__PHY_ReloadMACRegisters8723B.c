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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int IQK_MAC_REG_NUM ; 
 int /*<<< orphan*/  rtw_write32 (struct adapter*,int,int) ; 
 int /*<<< orphan*/  rtw_write8 (struct adapter*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _PHY_ReloadMACRegisters8723B(
	struct adapter *padapter, u32 *MACReg, u32 *MACBackup
)
{
	u32 i;

	for (i = 0 ; i < (IQK_MAC_REG_NUM - 1); i++) {
		rtw_write8(padapter, MACReg[i], (u8)MACBackup[i]);
	}
	rtw_write32(padapter, MACReg[i], MACBackup[i]);
}