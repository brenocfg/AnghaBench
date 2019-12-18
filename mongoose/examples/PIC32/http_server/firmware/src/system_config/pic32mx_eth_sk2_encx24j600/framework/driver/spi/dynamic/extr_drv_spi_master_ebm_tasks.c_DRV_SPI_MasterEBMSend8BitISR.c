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
struct DRV_SPI_DRIVER_OBJECT {size_t symbolsInProgress; int txEnabled; int rxEnabled; TYPE_1__* currentJob; int /*<<< orphan*/  spiId; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {scalar_t__ dataLeftToTx; size_t* txBuffer; size_t dataTxed; scalar_t__ dummyLeftToTx; } ;
typedef  int /*<<< orphan*/  SPI_MODULE_ID ;
typedef  TYPE_1__ DRV_SPI_JOB_OBJECT ;

/* Variables and functions */
 size_t MAX (size_t,int /*<<< orphan*/ ) ; 
 size_t MIN (scalar_t__,size_t) ; 
 int /*<<< orphan*/  PLIB_SPI_BufferWrite (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PLIB_SPI_FIFOCountGet (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_SPI_FIFOInterruptModeSelect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t PLIB_SPI_TX_8BIT_FIFO_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_FIFO_INTERRUPT_WHEN_TRANSMIT_BUFFER_IS_COMPLETELY_EMPTY ; 
 int /*<<< orphan*/  SPI_FIFO_TYPE_TRANSMIT ; 

int32_t DRV_SPI_MasterEBMSend8BitISR( struct DRV_SPI_DRIVER_OBJECT * pDrvInstance )
{
    register SPI_MODULE_ID spiId = pDrvInstance->spiId;
    register DRV_SPI_JOB_OBJECT * currentJob = pDrvInstance->currentJob;

    /* Determine the maximum number of bytes we can send to the FIFO*/
        uint8_t symbolsInTransit = MAX(pDrvInstance->symbolsInProgress, PLIB_SPI_FIFOCountGet(spiId, SPI_FIFO_TYPE_TRANSMIT));
        uint8_t bufferBytes = PLIB_SPI_TX_8BIT_FIFO_SIZE(spiId) - symbolsInTransit;
    /* Figure out how much data we can send*/
    size_t dataUnits = MIN(currentJob->dataLeftToTx, bufferBytes);

    size_t counter;

    if (dataUnits != 0)
    {
        /* Adjust the maximum buffer size downwards based on how much data we'll be sending*/
        bufferBytes -= dataUnits;
        currentJob->dataLeftToTx -= dataUnits;
        /* Set the location in the buffer of where to start sending from*/
        uint8_t *bufferLoc = &(currentJob->txBuffer[currentJob->dataTxed]);
        for (counter = 0; counter < dataUnits; counter++)
        {
            /* Send a unit/symbol of data*/
            PLIB_SPI_BufferWrite(spiId, bufferLoc[counter]);
        }
        /* Update the number of bytes transmitted*/
        currentJob->dataTxed += dataUnits;
        /* Adjust the symbols in progress */
        pDrvInstance->symbolsInProgress += dataUnits;
    }
    size_t dummyUnits = MIN(currentJob->dummyLeftToTx, bufferBytes);
    if (dummyUnits != 0)
    {
        currentJob->dummyLeftToTx -= dummyUnits;
        /* Adjust the symbols in progress */
        pDrvInstance->symbolsInProgress += dummyUnits;
        for (counter = 0; counter < dummyUnits; counter++)
        {
            PLIB_SPI_BufferWrite(spiId, 0xff);
        }
    }
    if (currentJob->dataLeftToTx + currentJob->dummyLeftToTx == 0)
    {
        /* We have no more data to send, turn off the TX interrupt*/
        PLIB_SPI_FIFOInterruptModeSelect(spiId, SPI_FIFO_INTERRUPT_WHEN_TRANSMIT_BUFFER_IS_COMPLETELY_EMPTY);
        pDrvInstance->txEnabled = false;

        /* Turn on the RX Interrupt*/
        pDrvInstance->rxEnabled = true;
    }
    return 0;
}