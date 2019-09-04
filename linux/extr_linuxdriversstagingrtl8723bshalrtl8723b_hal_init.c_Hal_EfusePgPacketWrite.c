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
typedef  int /*<<< orphan*/  u16 ;
struct adapter {int dummy; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  PGPKT_STRUCT ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_WIFI ; 
 int /*<<< orphan*/  hal_EfuseConstructPGPkt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hal_EfusePartialWriteCheck (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hal_EfusePgCheckAvailableAddr (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hal_EfusePgPacketWriteData (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hal_EfusePgPacketWriteHeader (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static s32 Hal_EfusePgPacketWrite(
	struct adapter *padapter,
	u8 offset,
	u8 word_en,
	u8 *pData,
	bool bPseudoTest
)
{
	PGPKT_STRUCT targetPkt;
	u16 startAddr = 0;
	u8 efuseType = EFUSE_WIFI;

	if (!hal_EfusePgCheckAvailableAddr(padapter, efuseType, bPseudoTest))
		return false;

	hal_EfuseConstructPGPkt(offset, word_en, pData, &targetPkt);

	if (!hal_EfusePartialWriteCheck(padapter, efuseType, &startAddr, &targetPkt, bPseudoTest))
		return false;

	if (!hal_EfusePgPacketWriteHeader(padapter, efuseType, &startAddr, &targetPkt, bPseudoTest))
		return false;

	if (!hal_EfusePgPacketWriteData(padapter, efuseType, &startAddr, &targetPkt, bPseudoTest))
		return false;

	return true;
}