#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned char* command; unsigned char* tx_cmd_pt; int tx_cmd_size; unsigned char* rx_cmd_pt; int rx_cmd_size; unsigned char* rx_data_pt; unsigned char* tx_data_pt; int rx_data_size; int tx_data_size; } ;
struct TYPE_6__ {TYPE_3__* pDataFlashDesc; TYPE_1__* pDevice; } ;
struct TYPE_5__ {unsigned int pages_size; int pages_number; unsigned int byte_mask; } ;
typedef  int /*<<< orphan*/  AT91S_DataFlashStatus ;
typedef  TYPE_2__* AT91PS_DataFlash ;

/* Variables and functions */
 int /*<<< orphan*/  AT91C_DATAFLASH_BAD_ADDRESS ; 
 int /*<<< orphan*/  AT91C_DATAFLASH_BAD_COMMAND ; 
 int /*<<< orphan*/  AT91F_SpiWrite (TYPE_3__*) ; 
 unsigned char DB_BUF1_WRITE ; 
 unsigned char DB_BUF2_WRITE ; 

__attribute__((used)) static AT91S_DataFlashStatus AT91F_DataFlashWriteBuffer(
	AT91PS_DataFlash pDataFlash,
	unsigned char BufferCommand,
	unsigned char *dataBuffer,
	unsigned int bufferAddress,
	int SizeToWrite )
{
	int cmdsize;
	/* Test if the buffer command is legal */
	if ((BufferCommand != DB_BUF1_WRITE) && (BufferCommand != DB_BUF2_WRITE))
		return AT91C_DATAFLASH_BAD_COMMAND;

	/* buffer address must be lower than page size */
	if (bufferAddress > pDataFlash->pDevice->pages_size)
		return AT91C_DATAFLASH_BAD_ADDRESS;

    	/* Send first Write Command */
	pDataFlash->pDataFlashDesc->command[0] = BufferCommand;
	pDataFlash->pDataFlashDesc->command[1] = 0;
	if (pDataFlash->pDevice->pages_number >= 16384)
	{
	   	pDataFlash->pDataFlashDesc->command[2] = 0;
	   	pDataFlash->pDataFlashDesc->command[3] = (unsigned char)(((unsigned int)(bufferAddress &  pDataFlash->pDevice->byte_mask)) >> 8) ;
	   	pDataFlash->pDataFlashDesc->command[4] = (unsigned char)((unsigned int)bufferAddress  & 0x00FF) ;
		cmdsize = 5;
	}
	else
	{
	   	pDataFlash->pDataFlashDesc->command[2] = (unsigned char)(((unsigned int)(bufferAddress &  pDataFlash->pDevice->byte_mask)) >> 8) ;
	   	pDataFlash->pDataFlashDesc->command[3] = (unsigned char)((unsigned int)bufferAddress  & 0x00FF) ;
	   	pDataFlash->pDataFlashDesc->command[4] = 0;
		cmdsize = 4;
	}
		
	pDataFlash->pDataFlashDesc->tx_cmd_pt 	 = pDataFlash->pDataFlashDesc->command ;
	pDataFlash->pDataFlashDesc->tx_cmd_size  = cmdsize ;
	pDataFlash->pDataFlashDesc->rx_cmd_pt 	 = pDataFlash->pDataFlashDesc->command ;
	pDataFlash->pDataFlashDesc->rx_cmd_size  = cmdsize ;

	pDataFlash->pDataFlashDesc->rx_data_pt 	 = dataBuffer ;
	pDataFlash->pDataFlashDesc->tx_data_pt 	 = dataBuffer ;
	pDataFlash->pDataFlashDesc->rx_data_size = SizeToWrite ;
	pDataFlash->pDataFlashDesc->tx_data_size = SizeToWrite ;

	return AT91F_SpiWrite(pDataFlash->pDataFlashDesc);
}