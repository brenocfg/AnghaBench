#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dataOut ;
typedef  int UINT16 ;
struct TYPE_7__ {scalar_t__ Data; } ;
struct TYPE_6__ {int /*<<< orphan*/  const member_1; int /*<<< orphan*/  const member_0; } ;
struct TYPE_9__ {TYPE_2__ DataOut; TYPE_1__ member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  const* NFCID1; int /*<<< orphan*/  Tg; } ;
typedef  TYPE_3__* PPN532_TARGET_TYPE_A ;
typedef  TYPE_4__ PN532_DATA_EXCHANGE_MIFARE ;
typedef  int /*<<< orphan*/  PKULL_M_PN532_COMM ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ MIFARE_CLASSIC_KEY_SIZE ; 
 scalar_t__ MIFARE_CLASSIC_UID_SIZE ; 
 int /*<<< orphan*/  PN532_CMD_InDataExchange ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__,int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ kull_m_pn532_sendrecv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 

BOOL kull_m_pn532_Mifare_Classic_AuthBlock(PKULL_M_PN532_COMM comm, PPN532_TARGET_TYPE_A target, const BYTE authKey, const BYTE blockId, const BYTE key[MIFARE_CLASSIC_KEY_SIZE])
{
	BOOL status = FALSE;
	PN532_DATA_EXCHANGE_MIFARE authBlock = {target->Tg, {authKey, blockId}};
	BYTE dataOut;
	UINT16 wOut = sizeof(dataOut);
	RtlCopyMemory(authBlock.DataOut.Data, key, MIFARE_CLASSIC_KEY_SIZE);
	RtlCopyMemory(authBlock.DataOut.Data + MIFARE_CLASSIC_KEY_SIZE, target->NFCID1, MIFARE_CLASSIC_UID_SIZE/*target->Target.TypeA.NFCIDLength*/); // !
	if(kull_m_pn532_sendrecv(comm, PN532_CMD_InDataExchange, (PBYTE) &authBlock, 13, &dataOut, &wOut))
		status = !dataOut;
	return status;
}