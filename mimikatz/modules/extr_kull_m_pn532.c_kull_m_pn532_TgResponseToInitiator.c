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
typedef  int /*<<< orphan*/  dataOut ;
typedef  int /*<<< orphan*/  dataIn ;
typedef  int UINT16 ;
typedef  int /*<<< orphan*/  PKULL_M_PN532_COMM ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  PN532_CMD_TgResponseToInitiator ; 
 int /*<<< orphan*/  PN532_MAX_LEN ; 
 int /*<<< orphan*/  kull_m_pn532_sendrecv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int*,int*) ; 

void kull_m_pn532_TgResponseToInitiator(PKULL_M_PN532_COMM comm)
{
	BYTE dataIn[3] = {0x01, 0x20, 0x01};
	BYTE dataOut[PN532_MAX_LEN - 2];
	UINT16 wOut = sizeof(dataOut);

	kull_m_pn532_sendrecv(comm, PN532_CMD_TgResponseToInitiator, dataIn, sizeof(dataIn), dataOut, &wOut);
}