#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int MCI_ARGR; unsigned int MCI_SR; int /*<<< orphan*/  MCI_CMDR; } ;
struct TYPE_7__ {TYPE_1__* pMCI_DeviceFeatures; } ;
struct TYPE_6__ {int Relative_Card_Address; } ;
typedef  TYPE_2__* AT91PS_MciDevice ;

/* Variables and functions */
 int /*<<< orphan*/  AT91C_APP_CMD ; 
 TYPE_5__* AT91C_BASE_MCI ; 
 int AT91C_CMD_SEND_ERROR ; 
 unsigned int AT91C_MCI_CMDRDY ; 
 int AT91C_MCI_SR_ERROR ; 
 scalar_t__ AT91C_SDCARD_APP_ALL_CMD ; 
 int AT91F_MCI_SendCommand (TYPE_2__*,unsigned int,unsigned int) ; 

int AT91F_MCI_SDCard_SendAppCommand (
	AT91PS_MciDevice pMCI_Device,
	unsigned int Cmd_App,
	unsigned int Arg	)
{
	unsigned int status;
	//unsigned int	tick=0;

	// Send the CMD55 for application specific command
    AT91C_BASE_MCI->MCI_ARGR = (pMCI_Device->pMCI_DeviceFeatures->Relative_Card_Address << 16 );
    AT91C_BASE_MCI->MCI_CMDR = AT91C_APP_CMD;

	// wait for CMDRDY Status flag to read the response
	do
	{
		status = AT91C_BASE_MCI->MCI_SR;
		//tick++;
	}
	while( !(status & AT91C_MCI_CMDRDY) );//&& (tick<100) );	

    // if an error occurs
    if (((AT91C_BASE_MCI->MCI_SR) & AT91C_MCI_SR_ERROR) != 0 )
		return ((AT91C_BASE_MCI->MCI_SR) & AT91C_MCI_SR_ERROR);

    // check if it is a specific command and then send the command
	if ( (Cmd_App && AT91C_SDCARD_APP_ALL_CMD) == 0)
		return AT91C_CMD_SEND_ERROR;

   return( AT91F_MCI_SendCommand(pMCI_Device,Cmd_App,Arg) );
}