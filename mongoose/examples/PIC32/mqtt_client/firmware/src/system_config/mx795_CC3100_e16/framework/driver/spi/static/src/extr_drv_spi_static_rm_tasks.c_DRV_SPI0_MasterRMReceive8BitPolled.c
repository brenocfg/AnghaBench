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
struct DRV_SPI_OBJ {scalar_t__ symbolsInProgress; TYPE_1__* currentJob; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {scalar_t__ dataLeftToRx; size_t dataRxed; int /*<<< orphan*/  dummyLeftToRx; int /*<<< orphan*/ * rxBuffer; } ;
typedef  TYPE_1__ DRV_SPI_JOB_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  PLIB_SPI_BufferRead (int /*<<< orphan*/ ) ; 
 scalar_t__ PLIB_SPI_ReceiverBufferIsFull (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_ID_1 ; 

int32_t DRV_SPI0_MasterRMReceive8BitPolled( struct DRV_SPI_OBJ * pDrvObj )
{
    register DRV_SPI_JOB_OBJECT * currentJob = pDrvObj->currentJob;

    if (currentJob == NULL)
    {
        return 0;
    }
    if (PLIB_SPI_ReceiverBufferIsFull(SPI_ID_1))
    {
        /* We have data waiting in the SPI buffer */
        if (currentJob->dataLeftToRx != 0)
        {
            /* Receive the data and updates the count */
            currentJob->rxBuffer[currentJob->dataRxed] = PLIB_SPI_BufferRead(SPI_ID_1);
            currentJob->dataRxed++;
            currentJob->dataLeftToRx --;
        }
        else
        {
            /* No Data but dummy data: Note: We cannot just clear the
               buffer because we have to keep track of how many symbols/units we
               have received, and the number may have increased since we checked
               how full the buffer is.*/
            PLIB_SPI_BufferRead(SPI_ID_1);
            //SYS_CONSOLE_MESSAGE("Rd ");
            currentJob->dummyLeftToRx--;
        }
        /* No longer have a symbol in progress */
        pDrvObj->symbolsInProgress = 0;
    }

    return 0;
}