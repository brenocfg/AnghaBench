#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_2__ {scalar_t__ (* ReadWlanInterruptPin ) () ;int /*<<< orphan*/ * pucTxCommandBuffer; int /*<<< orphan*/  (* WriteWlanPin ) (int /*<<< orphan*/ ) ;scalar_t__ pucReceivedData; scalar_t__ usEventOrDataReceived; scalar_t__ slTransmitDataError; scalar_t__ usRxDataPending; scalar_t__ usBufferSize; scalar_t__ usSlBufferLength; scalar_t__ usNumberOfFreeBuffers; scalar_t__ usRxEventOpcode; scalar_t__ NumberOfReleasedPackets; scalar_t__ NumberOfSentPackets; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_CMND_READ_BUFFER_SIZE ; 
 int /*<<< orphan*/  SimpleLinkWaitEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SimpleLink_Init_Start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpiOpen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpiReceiveHandler ; 
 scalar_t__ TIMEOUT ; 
 int /*<<< orphan*/  WLAN_ENABLE ; 
 int /*<<< orphan*/  hci_command_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 () ; 
 scalar_t__ stub4 () ; 
 scalar_t__ stub5 () ; 
 TYPE_1__ tSLInformation ; 
 scalar_t__ wlan_tx_buffer ; 

int wlan_start(UINT16 usPatchesAvailableAtHost)
{

	UINT32 ulSpiIRQState;
	UINT32 wlan_timeout;

	tSLInformation.NumberOfSentPackets = 0;
	tSLInformation.NumberOfReleasedPackets = 0;
	tSLInformation.usRxEventOpcode = 0;
	tSLInformation.usNumberOfFreeBuffers = 0;
	tSLInformation.usSlBufferLength = 0;
	tSLInformation.usBufferSize = 0;
	tSLInformation.usRxDataPending = 0;
	tSLInformation.slTransmitDataError = 0;
	tSLInformation.usEventOrDataReceived = 0;
	tSLInformation.pucReceivedData = 0;

	// Allocate the memory for the RX/TX data transactions
	tSLInformation.pucTxCommandBuffer = (UINT8 *)wlan_tx_buffer;

	// init spi
	SpiOpen(SpiReceiveHandler);

	// Check the IRQ line
	ulSpiIRQState = tSLInformation.ReadWlanInterruptPin();

	// Chip enable: toggle WLAN EN line
	tSLInformation.WriteWlanPin( WLAN_ENABLE );
    
    wlan_timeout = TIMEOUT;
	if (ulSpiIRQState) {
		// wait till the IRQ line goes low
		while(tSLInformation.ReadWlanInterruptPin() != 0 && --wlan_timeout)
		{
		}
	}
	else
	{
		// wait till the IRQ line goes high and than low
		while(tSLInformation.ReadWlanInterruptPin() == 0 && --wlan_timeout)
		{
		}

        if (wlan_timeout == 0) {
            return -1;
        }

        wlan_timeout = TIMEOUT;
		while(tSLInformation.ReadWlanInterruptPin() != 0 && --wlan_timeout)
		{
		}
	}

    if (wlan_timeout ==0) {
        return -1;
    }

	SimpleLink_Init_Start(usPatchesAvailableAtHost);

	// Read Buffer's size and finish
	hci_command_send(HCI_CMND_READ_BUFFER_SIZE, tSLInformation.pucTxCommandBuffer, 0);
	SimpleLinkWaitEvent(HCI_CMND_READ_BUFFER_SIZE, 0);

    return 0;
}