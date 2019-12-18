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
struct TYPE_2__ {unsigned int MCI_ARGR; unsigned int MCI_CMDR; unsigned int MCI_SR; } ;
typedef  int /*<<< orphan*/  AT91PS_MciDevice ;

/* Variables and functions */
 TYPE_1__* AT91C_BASE_MCI ; 
 int AT91C_CMD_SEND_OK ; 
 unsigned int AT91C_MCI_CMDRDY ; 
 unsigned int AT91C_MCI_RCRCE ; 
 int AT91C_MCI_SR_ERROR ; 
 unsigned int AT91C_MMC_SEND_OP_COND_CMD ; 
 unsigned int AT91C_SDCARD_APP_OP_COND_CMD ; 

int AT91F_MCI_SendCommand (
	AT91PS_MciDevice pMCI_Device,
	unsigned int Cmd,
	unsigned int Arg)
{
	unsigned int	error,status;
	//unsigned int	tick=0;

    // Send the command
    AT91C_BASE_MCI->MCI_ARGR = Arg;
    AT91C_BASE_MCI->MCI_CMDR = Cmd;

	// wait for CMDRDY Status flag to read the response
	do
	{
		status = AT91C_BASE_MCI->MCI_SR;
		//tick++;
	}
	while( !(status & AT91C_MCI_CMDRDY) );//&& (tick<100) );

    // Test error  ==> if crc error and response R3 ==> don't check error
    error = (AT91C_BASE_MCI->MCI_SR) & AT91C_MCI_SR_ERROR;
	if(error != 0 )
	{
		// if the command is SEND_OP_COND the CRC error flag is always present (cf : R3 response)
		if ( (Cmd != AT91C_SDCARD_APP_OP_COND_CMD) && (Cmd != AT91C_MMC_SEND_OP_COND_CMD) )
			return ((AT91C_BASE_MCI->MCI_SR) & AT91C_MCI_SR_ERROR);
		else
		{
			if (error != AT91C_MCI_RCRCE)
				return ((AT91C_BASE_MCI->MCI_SR) & AT91C_MCI_SR_ERROR);
		}
	}
    return AT91C_CMD_SEND_OK;
}