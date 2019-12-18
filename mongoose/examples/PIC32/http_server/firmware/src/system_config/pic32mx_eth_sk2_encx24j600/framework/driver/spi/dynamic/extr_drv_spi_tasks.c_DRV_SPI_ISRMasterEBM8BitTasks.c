#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct DRV_SPI_DRIVER_OBJECT {int txEnabled; scalar_t__ currentBaudRate; int rxEnabled; int /*<<< orphan*/  txInterruptSource; int /*<<< orphan*/  rxInterruptSource; int /*<<< orphan*/  errInterruptSource; TYPE_1__* currentJob; int /*<<< orphan*/  queue; int /*<<< orphan*/  spiClk; scalar_t__ symbolsInProgress; int /*<<< orphan*/  spiId; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_5__ {scalar_t__ baudRate; int /*<<< orphan*/  (* operationEnded ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* operationStarting ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {scalar_t__ dataLeftToTx; scalar_t__ dummyLeftToTx; size_t dataLeftToRx; size_t dummyLeftToRx; int /*<<< orphan*/  context; scalar_t__ pClient; int /*<<< orphan*/  (* completeCB ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  SPI_MODULE_ID ;
typedef  TYPE_1__ DRV_SPI_JOB_OBJECT ;
typedef  TYPE_2__ DRV_SPI_CLIENT_OBJECT ;
typedef  int /*<<< orphan*/  DRV_SPI_BUFFER_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_SPI_BUFFER_EVENT_COMPLETE ; 
 int /*<<< orphan*/  DRV_SPI_BUFFER_EVENT_PROCESSING ; 
 int /*<<< orphan*/  DRV_SPI_ISRErrorTasks (struct DRV_SPI_DRIVER_OBJECT*) ; 
 int /*<<< orphan*/  DRV_SPI_MasterEBMReceive8BitISR (struct DRV_SPI_DRIVER_OBJECT*) ; 
 int /*<<< orphan*/  DRV_SPI_MasterEBMSend8BitISR (struct DRV_SPI_DRIVER_OBJECT*) ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_Dequeue (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_FreeElement (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  DRV_SPI_SYS_QUEUE_IsEmpty (int /*<<< orphan*/ ) ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_SUCCESS ; 
 int /*<<< orphan*/  PLIB_SPI_BaudRateSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PLIB_SPI_BufferClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLIB_SPI_FIFOInterruptModeSelect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PLIB_SPI_RX_8BIT_FIFO_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_FIFO_INTERRUPT_WHEN_RECEIVE_BUFFER_IS_1HALF_FULL_OR_MORE ; 
 int /*<<< orphan*/  SPI_FIFO_INTERRUPT_WHEN_TRANSMIT_BUFFER_IS_1HALF_EMPTY_OR_MORE ; 
 int /*<<< orphan*/  SYS_ASSERT (int,char*) ; 
 int /*<<< orphan*/  SYS_CLK_PeripheralFrequencyGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_INT_SourceDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_INT_SourceEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_INT_SourceStatusClear (int /*<<< orphan*/ ) ; 
 scalar_t__ SYS_INT_SourceStatusGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int32_t DRV_SPI_ISRMasterEBM8BitTasks ( struct DRV_SPI_DRIVER_OBJECT * pDrvInstance )
{
    volatile bool continueLoop;

    /* Disable the interrupts */
    SYS_INT_SourceDisable(pDrvInstance->rxInterruptSource);
    SYS_INT_SourceDisable(pDrvInstance->txInterruptSource);
    SYS_INT_SourceDisable(pDrvInstance->errInterruptSource);
    do {

        DRV_SPI_JOB_OBJECT * currentJob = pDrvInstance->currentJob;
        SPI_MODULE_ID spiId = pDrvInstance->spiId;
        /* Check for a new task */
        if (pDrvInstance->currentJob == NULL)
        {
            if (DRV_SPI_SYS_QUEUE_Dequeue(pDrvInstance->queue, (void *)&(pDrvInstance->currentJob)) != DRV_SPI_SYS_QUEUE_SUCCESS)
            {
                SYS_ASSERT(false, "\r\nSPI Driver: Error in dequeing.");
                return 0;
            }
            if (pDrvInstance->currentJob == NULL)
            {
                pDrvInstance->txEnabled = false;
                return 0;
            }
            currentJob = pDrvInstance->currentJob;

            pDrvInstance->symbolsInProgress = 0;

            /* Call the operation starting function pointer.  This can be used to modify the slave select lines */
            DRV_SPI_CLIENT_OBJECT * pClient = (DRV_SPI_CLIENT_OBJECT*)currentJob->pClient;
            if (pClient->operationStarting != NULL)
            {
                (*pClient->operationStarting)(DRV_SPI_BUFFER_EVENT_PROCESSING, (DRV_SPI_BUFFER_HANDLE)currentJob, currentJob->context);
            }
            /* Check the baud rate.  If its different set the new baud rate*/
            if (pClient->baudRate != pDrvInstance->currentBaudRate)
            {
                PLIB_SPI_BaudRateSet( spiId , SYS_CLK_PeripheralFrequencyGet(pDrvInstance->spiClk), pClient->baudRate );
                pDrvInstance->currentBaudRate = pClient->baudRate;
            }

            /* List the new job as processing*/
            currentJob->status = DRV_SPI_BUFFER_EVENT_PROCESSING;
            if (currentJob->dataLeftToTx +currentJob->dummyLeftToTx > PLIB_SPI_RX_8BIT_FIFO_SIZE(spiId))
            {
                PLIB_SPI_FIFOInterruptModeSelect(spiId, SPI_FIFO_INTERRUPT_WHEN_TRANSMIT_BUFFER_IS_1HALF_EMPTY_OR_MORE);
                PLIB_SPI_FIFOInterruptModeSelect(spiId, SPI_FIFO_INTERRUPT_WHEN_RECEIVE_BUFFER_IS_1HALF_FULL_OR_MORE);
            }
            /* Flush out the Receive buffer */
            PLIB_SPI_BufferClear(spiId);
        }


        continueLoop = false;
        /* Execute the sub tasks */
             if
            (currentJob->dataLeftToTx +currentJob->dummyLeftToTx != 0)
        {
            DRV_SPI_MasterEBMSend8BitISR(pDrvInstance);
        }

        DRV_SPI_ISRErrorTasks(pDrvInstance);

        /* Figure out how many bytes are left to be received */
        volatile size_t bytesLeft = currentJob->dataLeftToRx + currentJob->dummyLeftToRx;
        // Check to see if we have any data left to receive and update the bytes left.

        if (bytesLeft != 0)
        {
            DRV_SPI_MasterEBMReceive8BitISR(pDrvInstance);
            bytesLeft = currentJob->dataLeftToRx + currentJob->dummyLeftToRx;
        }

        if (bytesLeft == 0)
        {
                    // Disable the interrupt, or more correctly don't re-enable it later*/
                    pDrvInstance->rxEnabled = false;
                    /* Job is complete*/
                    currentJob->status = DRV_SPI_BUFFER_EVENT_COMPLETE;
                    /* Call the job complete call back*/
                    if (currentJob->completeCB != NULL)
                    {
                        (*currentJob->completeCB)(DRV_SPI_BUFFER_EVENT_COMPLETE, (DRV_SPI_BUFFER_HANDLE)currentJob, currentJob->context);
                    }
                    /* Call the operation complete call back.  This is different than the
                       job complete callback.  This can be used to modify the Slave Select line.
                       The job complete callback can be used to free a client that is blocked
                       waiting for complete*/
                    DRV_SPI_CLIENT_OBJECT * pClient = (DRV_SPI_CLIENT_OBJECT*)currentJob->pClient;
                    if (pClient->operationEnded != NULL)
                    {
                        (*pClient->operationEnded)(DRV_SPI_BUFFER_EVENT_COMPLETE, (DRV_SPI_BUFFER_HANDLE)currentJob, currentJob->context);
                    }
                    /* Return the job back to the free queue*/
                    if (DRV_SPI_SYS_QUEUE_FreeElement(pDrvInstance->queue, currentJob) != DRV_SPI_SYS_QUEUE_SUCCESS)
                    {
                        SYS_ASSERT(false, "\r\nSPI Driver: Queue free element error.");
                        return 0;
                    }
                    /* Clean up */
                    pDrvInstance->currentJob = NULL;
                    if (!DRV_SPI_SYS_QUEUE_IsEmpty(pDrvInstance->queue))
                    {
                        continueLoop = true;
                        continue;
                    }
                    else
                    {
                        break;
                    }
                }


        /* Check to see if the interrupts would fire again if so just go back into
           the loop instead of suffering the interrupt latency of exiting and re-entering*/
        if (pDrvInstance->currentJob != NULL)
        {
            /* Clear the Interrupts */
            SYS_INT_SourceStatusClear(pDrvInstance->rxInterruptSource);
            SYS_INT_SourceStatusClear(pDrvInstance->txInterruptSource);
            SYS_INT_SourceStatusClear(pDrvInstance->errInterruptSource);
            /* Interrupts should immediately become active again if they're in a fired condition */
            if ((SYS_INT_SourceStatusGet(pDrvInstance->rxInterruptSource)) ||
                (SYS_INT_SourceStatusGet(pDrvInstance->txInterruptSource)) ||
                (SYS_INT_SourceStatusGet(pDrvInstance->errInterruptSource)))
            {
                /* Interrupt would fire again anyway so we should just go back to the start*/
                continueLoop = true;
                continue;
            }
            /* If we're here then we know that the interrupt should not be firing again immediately, so re-enable them and exit*/
            SYS_INT_SourceEnable(pDrvInstance->rxInterruptSource);
            SYS_INT_SourceEnable(pDrvInstance->txInterruptSource);

            return 0;
        }

    } while(continueLoop);
    /* if we're here it means that we have no more jobs in the queue, tx and rx interrupts will be re-enabled by the BufferAdd* functions*/
    SYS_INT_SourceStatusClear(pDrvInstance->rxInterruptSource);
    SYS_INT_SourceStatusClear(pDrvInstance->txInterruptSource);
    return 0;
}