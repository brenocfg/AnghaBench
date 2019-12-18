#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t dataLeftToTx; size_t dataLeftToRx; size_t dummyLeftToTx; size_t dummyLeftToRx; int /*<<< orphan*/  status; void* context; int /*<<< orphan*/  completeCB; void* rxBuffer; void* txBuffer; } ;
struct TYPE_5__ {int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ DRV_SPI_OBJ ;
typedef  TYPE_2__ DRV_SPI_JOB_OBJECT ;
typedef  scalar_t__ DRV_SPI_BUFFER_HANDLE ;
typedef  int /*<<< orphan*/  DRV_SPI_BUFFER_EVENT_HANDLER ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_SPI_BUFFER_EVENT_PENDING ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_AllocElementLock (int /*<<< orphan*/ ,void**) ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_EnqueueLock (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ DRV_SPI_SYS_QUEUE_SUCCESS ; 
 int /*<<< orphan*/  SYS_ASSERT (int,char*) ; 
 TYPE_1__ gDrvSPI0Obj ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

DRV_SPI_BUFFER_HANDLE DRV_SPI0_BufferAddWriteRead2 ( void *txBuffer, size_t txSize, void *rxBuffer, size_t rxSize, DRV_SPI_BUFFER_EVENT_HANDLER completeCB, void * context, DRV_SPI_BUFFER_HANDLE * jobHandle )
{
    DRV_SPI_OBJ *dObj = (DRV_SPI_OBJ*)NULL;

    dObj = &gDrvSPI0Obj;

    DRV_SPI_JOB_OBJECT * pJob = NULL;
    if (DRV_SPI_SYS_QUEUE_AllocElementLock(dObj->queue, (void **)&pJob) != DRV_SPI_SYS_QUEUE_SUCCESS)
    {
        SYS_ASSERT(false, "\r\nSPI Driver: Error trying to get a free entry.");
        return (DRV_SPI_BUFFER_HANDLE)NULL;
    }

    memset(pJob, 0, sizeof(DRV_SPI_JOB_OBJECT));
    pJob->txBuffer = txBuffer;
    pJob->dataLeftToTx = txSize;
    pJob->rxBuffer = rxBuffer;
    pJob->dataLeftToRx = rxSize;

    if (jobHandle != NULL )
    {
        *jobHandle = (DRV_SPI_BUFFER_HANDLE)pJob;
    }
    if (rxSize > txSize)
    {
        pJob->dummyLeftToTx = rxSize - txSize;
    }
    if (txSize > rxSize)
    {
        pJob->dummyLeftToRx = txSize - rxSize;
    }
    pJob->completeCB = completeCB;
    pJob->context = context;
    pJob->status = DRV_SPI_BUFFER_EVENT_PENDING;

    if (DRV_SPI_SYS_QUEUE_EnqueueLock(dObj->queue, (void*)pJob) != DRV_SPI_SYS_QUEUE_SUCCESS)
    {
        SYS_ASSERT(false, "\r\nSPI Driver: Error enqueing new job.");
        return (DRV_SPI_BUFFER_HANDLE)NULL;
    }

    return (DRV_SPI_BUFFER_HANDLE)pJob;
}