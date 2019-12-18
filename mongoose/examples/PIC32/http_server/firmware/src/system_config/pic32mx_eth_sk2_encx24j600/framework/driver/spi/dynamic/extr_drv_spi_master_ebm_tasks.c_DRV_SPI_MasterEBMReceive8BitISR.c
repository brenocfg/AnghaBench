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
typedef  size_t uint8_t ;
struct DRV_SPI_DRIVER_OBJECT {size_t symbolsInProgress; TYPE_1__* currentJob; int /*<<< orphan*/  spiId; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {size_t dataLeftToRx; size_t* rxBuffer; size_t dataRxed; size_t dummyLeftToRx; } ;
typedef  int /*<<< orphan*/  SPI_MODULE_ID ;
typedef  TYPE_1__ DRV_SPI_JOB_OBJECT ;

/* Variables and functions */
 size_t MIN (size_t,size_t) ; 
 size_t PLIB_SPI_BufferRead (int /*<<< orphan*/ ) ; 
 size_t PLIB_SPI_FIFOCountGet (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_SPI_FIFOInterruptModeSelect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t PLIB_SPI_RX_8BIT_HW_MARK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_FIFO_INTERRUPT_WHEN_RECEIVE_BUFFER_IS_NOT_EMPTY ; 
 int /*<<< orphan*/  SPI_FIFO_TYPE_RECEIVE ; 

int32_t DRV_SPI_MasterEBMReceive8BitISR( struct DRV_SPI_DRIVER_OBJECT * pDrvInstance )
{
    register SPI_MODULE_ID spiId = pDrvInstance->spiId;
    register DRV_SPI_JOB_OBJECT * currentJob = pDrvInstance->currentJob;

    /* Figure out how many bytes are waiting to be received."*/
    uint8_t bufferBytes = PLIB_SPI_FIFOCountGet(spiId, SPI_FIFO_TYPE_RECEIVE);
    /* Calculate the maximum number of data bytes that can be received*/
    size_t dataUnits = MIN(currentJob->dataLeftToRx, bufferBytes);
    size_t counter;

    if (dataUnits != 0)
    {
        bufferBytes -= dataUnits;
        currentJob->dataLeftToRx -= dataUnits;
        /* Set the buffer location to receive bytes from the SPI to*/
        uint8_t *bufferLoc = &(currentJob->rxBuffer[currentJob->dataRxed]);
        for (counter = 0; counter < dataUnits; counter++)
        {
            /* Receive the data from the SPI */
            bufferLoc[counter] = PLIB_SPI_BufferRead(spiId);
        }
        /* Adjust the amount of data that has been received */
        currentJob->dataRxed += dataUnits;
        /* Update the symbols in progress so we can send more units later */
        pDrvInstance->symbolsInProgress -= dataUnits;
    }

    /* Figure out the maximum number of dummy data to be received */
    size_t dummyUnits = MIN(currentJob->dummyLeftToRx, bufferBytes);
    if (dummyUnits != 0)
    {
        /* Lower the number of dummy bytes to be received */
        currentJob->dummyLeftToRx -= dummyUnits;
        pDrvInstance->symbolsInProgress -= dummyUnits;
        for (counter = 0; counter < dummyUnits; counter++)
        {
            /* Receive and throw away the byte.  Note: We cannot just clear the
               buffer because we have to keep track of how many symbols/units we
               have received, and the number may have increased since we checked
               how full the buffer is.*/
            PLIB_SPI_BufferRead(spiId);
        }
    }

    /* Figure out how many bytes are left to be received */
    size_t bytesLeft = currentJob->dataLeftToRx + currentJob->dummyLeftToRx;

    /* If the bytes left are smaller than the HW mark we have to change the interrupt mode */
    if (bytesLeft < PLIB_SPI_RX_8BIT_HW_MARK(spiId))
    {
        PLIB_SPI_FIFOInterruptModeSelect(spiId, SPI_FIFO_INTERRUPT_WHEN_RECEIVE_BUFFER_IS_NOT_EMPTY);
    }
    return 0;
}