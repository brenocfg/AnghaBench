#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dataOut ;
typedef  int UINT16 ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int /*<<< orphan*/  const member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {TYPE_1__ member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {int /*<<< orphan*/  Tg; } ;
typedef  TYPE_2__* PPN532_TARGET_TYPE_A ;
typedef  TYPE_3__ PN532_DATA_EXCHANGE_MIFARE ;
typedef  TYPE_4__* PMIFARE_CLASSIC_RAW_BLOCK ;
typedef  int /*<<< orphan*/  PKULL_M_PN532_COMM ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int /*<<< orphan*/  MIFARE_CLASSIC_RAW_BLOCK ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  MIFARE_CLASSIC_BLOCK_SIZE ; 
 int /*<<< orphan*/  MIFARE_CLASSIC_CMD_READ ; 
 int /*<<< orphan*/  PN532_CMD_InDataExchange ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_4__*,int) ; 
 scalar_t__ kull_m_pn532_sendrecv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 

BOOL kull_m_pn532_Mifare_Classic_ReadBlock(PKULL_M_PN532_COMM comm, PPN532_TARGET_TYPE_A target, const BYTE blockId, PMIFARE_CLASSIC_RAW_BLOCK block)
{
	BOOL status = FALSE;
	PN532_DATA_EXCHANGE_MIFARE readBlock = {target->Tg, {MIFARE_CLASSIC_CMD_READ, blockId}};
	BYTE dataOut[MIFARE_CLASSIC_BLOCK_SIZE + 1];
	UINT16 wOut = sizeof(dataOut);
	RtlZeroMemory(block, sizeof(MIFARE_CLASSIC_RAW_BLOCK));
	if(kull_m_pn532_sendrecv(comm, PN532_CMD_InDataExchange, (PBYTE) &readBlock, 3, dataOut, &wOut))
		if(status = !dataOut[0])
			RtlCopyMemory(block->data, dataOut + 1, wOut - 1);
	return status;
}