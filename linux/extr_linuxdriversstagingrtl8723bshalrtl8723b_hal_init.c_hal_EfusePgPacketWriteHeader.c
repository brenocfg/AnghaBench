#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct adapter {int dummy; } ;
struct TYPE_5__ {scalar_t__ offset; } ;
typedef  TYPE_1__* PPGPKT_STRUCT ;

/* Variables and functions */
 scalar_t__ EFUSE_MAX_SECTION_BASE ; 
 int hal_EfusePgPacketWrite1ByteHeader (struct adapter*,int,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int hal_EfusePgPacketWrite2ByteHeader (struct adapter*,int,int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static u8 hal_EfusePgPacketWriteHeader(
	struct adapter *padapter,
	u8 efuseType,
	u16 *pAddr,
	PPGPKT_STRUCT pTargetPkt,
	u8 bPseudoTest
)
{
	u8 bRet = false;

	if (pTargetPkt->offset >= EFUSE_MAX_SECTION_BASE)
		bRet = hal_EfusePgPacketWrite2ByteHeader(padapter, efuseType, pAddr, pTargetPkt, bPseudoTest);
	else
		bRet = hal_EfusePgPacketWrite1ByteHeader(padapter, efuseType, pAddr, pTargetPkt, bPseudoTest);

	return bRet;
}