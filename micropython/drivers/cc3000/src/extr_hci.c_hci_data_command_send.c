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
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT16 ;

/* Variables and functions */
 scalar_t__ HCI_TYPE_DATA ; 
 scalar_t__ SIMPLE_LINK_HCI_DATA_CMND_HEADER_SIZE ; 
 int SPI_HEADER_SIZE ; 
 int /*<<< orphan*/  SpiWrite (scalar_t__*,scalar_t__) ; 
 scalar_t__* UINT16_TO_STREAM (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (scalar_t__*,scalar_t__) ; 

void hci_data_command_send(UINT16 usOpcode, UINT8 *pucBuff, UINT8 ucArgsLength,UINT16 ucDataLength)
{ 
	UINT8 *stream = (pucBuff + SPI_HEADER_SIZE);

	UINT8_TO_STREAM(stream, HCI_TYPE_DATA);
	UINT8_TO_STREAM(stream, usOpcode);
	UINT8_TO_STREAM(stream, ucArgsLength);
	stream = UINT16_TO_STREAM(stream, ucArgsLength + ucDataLength);

	// Send the command over SPI on data channel
	SpiWrite(pucBuff, ucArgsLength + ucDataLength + SIMPLE_LINK_HCI_DATA_CMND_HEADER_SIZE);

	return;
}