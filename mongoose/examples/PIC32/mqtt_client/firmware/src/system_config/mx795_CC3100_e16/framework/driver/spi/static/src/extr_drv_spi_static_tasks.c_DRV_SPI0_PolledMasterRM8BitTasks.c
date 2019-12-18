#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct DRV_SPI_OBJ {scalar_t__ numTrfsSmPolled; TYPE_1__* currentJob; int /*<<< orphan*/  queue; int /*<<< orphan*/  (* operationEnded ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* operationStarting ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ symbolsInProgress; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {scalar_t__ dataLeftToTx; scalar_t__ dummyLeftToTx; size_t dataLeftToRx; size_t dummyLeftToRx; int /*<<< orphan*/  context; int /*<<< orphan*/  (* completeCB ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ DRV_SPI_JOB_OBJECT ;
typedef  int /*<<< orphan*/  DRV_SPI_BUFFER_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_SPI0_MasterRMReceive8BitPolled (struct DRV_SPI_OBJ*) ; 
 int /*<<< orphan*/  DRV_SPI0_MasterRMSend8BitPolled (struct DRV_SPI_OBJ*) ; 
 int /*<<< orphan*/  DRV_SPI0_PolledErrorTasks (struct DRV_SPI_OBJ*) ; 
 int /*<<< orphan*/  DRV_SPI_BUFFER_EVENT_COMPLETE ; 
 int /*<<< orphan*/  DRV_SPI_BUFFER_EVENT_PROCESSING ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_DequeueLock (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_FreeElementLock (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_SUCCESS ; 
 int /*<<< orphan*/  PLIB_SPI_BufferClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_ID_1 ; 
 int /*<<< orphan*/  SYS_ASSERT (int,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int32_t DRV_SPI0_PolledMasterRM8BitTasks ( struct DRV_SPI_OBJ * dObj )
{
    volatile bool continueLoop;
    uint8_t counter = 0;
    uint8_t numPolled = dObj->numTrfsSmPolled;
    uint8_t result = 0;
    do {
        
        DRV_SPI_JOB_OBJECT * currentJob = dObj->currentJob;

        /* Check for a new task */
        if (dObj->currentJob == NULL)
        {
            if (DRV_SPI_SYS_QUEUE_DequeueLock(dObj->queue, (void *)&(dObj->currentJob)) != DRV_SPI_SYS_QUEUE_SUCCESS)
            {
                SYS_ASSERT(false, "\r\nSPI Driver: Error in dequeing.");
                return 0;
            }
            if (dObj->currentJob == NULL)
            {
                return 0;
            }
            currentJob = dObj->currentJob;

            dObj->symbolsInProgress = 0;

            /* Call the operation starting function pointer.  This can be used to modify the slave select lines */
            if (dObj->operationStarting != NULL)
            {
                (*dObj->operationStarting)(DRV_SPI_BUFFER_EVENT_PROCESSING, (DRV_SPI_BUFFER_HANDLE)currentJob, currentJob->context);
            }

            /* List the new job as processing*/
            currentJob->status = DRV_SPI_BUFFER_EVENT_PROCESSING;
            /* Flush out the Receive buffer */
            PLIB_SPI_BufferClear(SPI_ID_1);
        }


        continueLoop = false;
        
        /* Execute the sub tasks */
            if
            (currentJob->dataLeftToTx +currentJob->dummyLeftToTx != 0)
        {
            DRV_SPI0_MasterRMSend8BitPolled(dObj);
        }
        
        DRV_SPI0_PolledErrorTasks(dObj);
        
        /* Figure out how many bytes are left to be received */
        volatile size_t bytesLeft = currentJob->dataLeftToRx + currentJob->dummyLeftToRx;
        
        // Check to see if we have any data left to receive and update the bytes left.
        if (bytesLeft != 0)
        {
            DRV_SPI0_MasterRMReceive8BitPolled(dObj);
            bytesLeft = currentJob->dataLeftToRx + currentJob->dummyLeftToRx;
        }
        if (bytesLeft == 0)
        {
                    /* Job is complete*/
                    currentJob->status = DRV_SPI_BUFFER_EVENT_COMPLETE;
                    /* Call the job complete call back*/
                    if (currentJob->completeCB != NULL)
                    {
                        (*currentJob->completeCB)(DRV_SPI_BUFFER_EVENT_COMPLETE, (DRV_SPI_BUFFER_HANDLE)currentJob, currentJob->context);
                    }

                    /* Call the operation complete call back.  This is different than the
                       job complete callback.  This can be used to modify the Slave Select line.*/

                    if (dObj->operationEnded != NULL)
                    {
                        (*dObj->operationEnded)(DRV_SPI_BUFFER_EVENT_COMPLETE, (DRV_SPI_BUFFER_HANDLE)currentJob, currentJob->context);
                    }

                    /* Return the job back to the free queue*/
                    if (DRV_SPI_SYS_QUEUE_FreeElementLock(dObj->queue, currentJob) != DRV_SPI_SYS_QUEUE_SUCCESS)
                    {
                        SYS_ASSERT(false, "\r\nSPI Driver: Queue free element error.");
                        return 0;
                    }
                    /* Clean up */
                    dObj->currentJob = NULL;
                }


        counter ++;
        if ((counter < numPolled) && (result != 0))
        {
            continueLoop = true;
        }

    } while(continueLoop);
    return 0;
}