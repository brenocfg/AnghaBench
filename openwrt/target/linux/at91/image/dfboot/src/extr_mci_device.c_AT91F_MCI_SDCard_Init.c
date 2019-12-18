#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* pMCI_DeviceFeatures; } ;
struct TYPE_12__ {int Relative_Card_Address; int Max_Read_DataBlock_Length; int Max_Write_DataBlock_Length; int Sector_Size; unsigned int Read_Partial; unsigned int Write_Partial; unsigned int Erase_Block_Enable; unsigned int Read_Block_Misalignment; unsigned int Write_Block_Misalignment; unsigned int Memory_Capacity; int /*<<< orphan*/  Card_Inserted; } ;
struct TYPE_11__ {int* MCI_RSPR; } ;
typedef  TYPE_2__* AT91PS_MciDevice ;

/* Variables and functions */
 TYPE_10__* AT91C_BASE_MCI ; 
 scalar_t__ AT91C_CMD_SEND_OK ; 
 unsigned int AT91C_CSD_CSIZE_H_M ; 
 unsigned int AT91C_CSD_CSIZE_H_S ; 
 unsigned int AT91C_CSD_CSIZE_L_M ; 
 unsigned int AT91C_CSD_CSIZE_L_S ; 
 unsigned int AT91C_CSD_C_SIZE_M_M ; 
 unsigned int AT91C_CSD_C_SIZE_M_S ; 
 unsigned int AT91C_CSD_RD_B_LEN_M ; 
 unsigned int AT91C_CSD_RD_B_LEN_S ; 
 unsigned int AT91C_CSD_RD_B_MIS_M ; 
 unsigned int AT91C_CSD_RD_B_MIS_S ; 
 unsigned int AT91C_CSD_RD_B_PAR_M ; 
 unsigned int AT91C_CSD_RD_B_PAR_S ; 
 unsigned int AT91C_CSD_WBLEN_M ; 
 unsigned int AT91C_CSD_WBLEN_S ; 
 unsigned int AT91C_CSD_WBLOCK_P_M ; 
 unsigned int AT91C_CSD_WBLOCK_P_S ; 
 unsigned int AT91C_CSD_WR_B_MIS_M ; 
 unsigned int AT91C_CSD_WR_B_MIS_S ; 
 unsigned int AT91C_CSD_v21_ER_BLEN_EN_M ; 
 unsigned int AT91C_CSD_v21_ER_BLEN_EN_S ; 
 unsigned int AT91C_CSD_v21_SECT_SIZE_M ; 
 unsigned int AT91C_CSD_v21_SECT_SIZE_S ; 
 int /*<<< orphan*/  AT91C_GO_IDLE_STATE_CMD ; 
 scalar_t__ AT91C_INIT_ERROR ; 
 int AT91C_INIT_OK ; 
 int /*<<< orphan*/  AT91C_NO_ARGUMENT ; 
 int /*<<< orphan*/  AT91C_SD_CARD_INSERTED ; 
 int /*<<< orphan*/  AT91C_SET_RELATIVE_ADDR_CMD ; 
 scalar_t__ AT91F_MCI_GetCSD (TYPE_2__*,int,unsigned int*) ; 
 scalar_t__ AT91F_MCI_SDCard_GetCID (TYPE_2__*,unsigned int*) ; 
 scalar_t__ AT91F_MCI_SDCard_GetOCR (TYPE_2__*) ; 
 scalar_t__ AT91F_MCI_SDCard_SetBusWidth (TYPE_2__*) ; 
 scalar_t__ AT91F_MCI_SendCommand (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ AT91F_MCI_SetBlocklength (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 

int AT91F_MCI_SDCard_Init (AT91PS_MciDevice pMCI_Device)
{
    unsigned int	tab_response[4];
	unsigned int	mult,blocknr;

	AT91F_MCI_SendCommand(pMCI_Device, AT91C_GO_IDLE_STATE_CMD, AT91C_NO_ARGUMENT);

    if(AT91F_MCI_SDCard_GetOCR(pMCI_Device) == AT91C_INIT_ERROR)
    	return AT91C_INIT_ERROR;

	if (AT91F_MCI_SDCard_GetCID(pMCI_Device,tab_response) == AT91C_CMD_SEND_OK)
	{
	    pMCI_Device->pMCI_DeviceFeatures->Card_Inserted = AT91C_SD_CARD_INSERTED;

	    if (AT91F_MCI_SendCommand(pMCI_Device, AT91C_SET_RELATIVE_ADDR_CMD, 0) == AT91C_CMD_SEND_OK)
		{
			pMCI_Device->pMCI_DeviceFeatures->Relative_Card_Address = (AT91C_BASE_MCI->MCI_RSPR[0] >> 16);
			if (AT91F_MCI_GetCSD(pMCI_Device,pMCI_Device->pMCI_DeviceFeatures->Relative_Card_Address,tab_response) == AT91C_CMD_SEND_OK)
			{
		  		pMCI_Device->pMCI_DeviceFeatures->Max_Read_DataBlock_Length = 1 << ((tab_response[1] >> AT91C_CSD_RD_B_LEN_S) & AT91C_CSD_RD_B_LEN_M );
	 			pMCI_Device->pMCI_DeviceFeatures->Max_Write_DataBlock_Length =	1 << ((tab_response[3] >> AT91C_CSD_WBLEN_S) & AT91C_CSD_WBLEN_M );
				pMCI_Device->pMCI_DeviceFeatures->Sector_Size = 1 + ((tab_response[2] >> AT91C_CSD_v21_SECT_SIZE_S) & AT91C_CSD_v21_SECT_SIZE_M );
		  		pMCI_Device->pMCI_DeviceFeatures->Read_Partial = (tab_response[1] >> AT91C_CSD_RD_B_PAR_S) & AT91C_CSD_RD_B_PAR_M;
				pMCI_Device->pMCI_DeviceFeatures->Write_Partial = (tab_response[3] >> AT91C_CSD_WBLOCK_P_S) & AT91C_CSD_WBLOCK_P_M;
				pMCI_Device->pMCI_DeviceFeatures->Erase_Block_Enable = (tab_response[3] >> AT91C_CSD_v21_ER_BLEN_EN_S) & AT91C_CSD_v21_ER_BLEN_EN_M;
				pMCI_Device->pMCI_DeviceFeatures->Read_Block_Misalignment = (tab_response[1] >> AT91C_CSD_RD_B_MIS_S) & AT91C_CSD_RD_B_MIS_M;
				pMCI_Device->pMCI_DeviceFeatures->Write_Block_Misalignment = (tab_response[1] >> AT91C_CSD_WR_B_MIS_S) & AT91C_CSD_WR_B_MIS_M;

				//// Compute Memory Capacity
					// compute MULT
					mult = 1 << ( ((tab_response[2] >> AT91C_CSD_C_SIZE_M_S) & AT91C_CSD_C_SIZE_M_M) + 2 );
					// compute MSB of C_SIZE
					blocknr = ((tab_response[1] >> AT91C_CSD_CSIZE_H_S) & AT91C_CSD_CSIZE_H_M) << 2;
					// compute MULT * (LSB of C-SIZE + MSB already computed + 1) = BLOCKNR
					blocknr = mult * ( ( blocknr + ( (tab_response[2] >> AT91C_CSD_CSIZE_L_S) & AT91C_CSD_CSIZE_L_M) ) + 1 );

					pMCI_Device->pMCI_DeviceFeatures->Memory_Capacity =  pMCI_Device->pMCI_DeviceFeatures->Max_Read_DataBlock_Length * blocknr;
			  	//// End of Compute Memory Capacity
					printf("SD-Card: %d Bytes\n\r", pMCI_Device->pMCI_DeviceFeatures->Memory_Capacity);

		  		if( AT91F_MCI_SDCard_SetBusWidth(pMCI_Device) == AT91C_CMD_SEND_OK )
				{	
					 if (AT91F_MCI_SetBlocklength(pMCI_Device,pMCI_Device->pMCI_DeviceFeatures->Max_Read_DataBlock_Length) == AT91C_CMD_SEND_OK)
					return AT91C_INIT_OK;
				}
			}
		}
	}
    return AT91C_INIT_ERROR;
}