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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct DRV_SPI_DRIVER_OBJECT {int /*<<< orphan*/  txDmaChannelHandle; int /*<<< orphan*/  spiId; TYPE_1__* currentJob; } ;
struct TYPE_2__ {scalar_t__ dataLeftToTx; size_t dataTxed; int /*<<< orphan*/  txDMAProgressStage; int /*<<< orphan*/ * txBuffer; } ;
typedef  scalar_t__ SYS_DMA_TRANSFER_EVENT ;
typedef  int /*<<< orphan*/  SYS_DMA_CHANNEL_HANDLE ;
typedef  TYPE_1__ DRV_SPI_JOB_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_SPI_DMA_COMPLETE ; 
 int /*<<< orphan*/  DRV_SPI_DMA_DATA_INPROGRESS ; 
 scalar_t__ DRV_SPI_DMA_TXFER_SIZE ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ PLIB_DMA_MAX_TRF_SIZE ; 
 void* PLIB_SPI_BufferAddressGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_DMA_ChannelTransferAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,void*,int,int) ; 
 scalar_t__ SYS_DMA_TRANSFER_EVENT_COMPLETE ; 

void DRV_SPI_MasterDMASendData8BitISR(SYS_DMA_TRANSFER_EVENT event, SYS_DMA_CHANNEL_HANDLE handle, uintptr_t contextHandle)
{
    if (event != SYS_DMA_TRANSFER_EVENT_COMPLETE)
    {
        // Ignore for now
        return;
    }
    struct DRV_SPI_DRIVER_OBJECT * pDrvInstance = (struct DRV_SPI_DRIVER_OBJECT *)contextHandle;
    DRV_SPI_JOB_OBJECT * currentJob = pDrvInstance->currentJob;
    if (currentJob->dataLeftToTx != 0)
    {
            uint8_t * ptr = &(currentJob->txBuffer[currentJob->dataTxed]);
            uint32_t len = MIN(MIN(PLIB_DMA_MAX_TRF_SIZE, currentJob->dataLeftToTx), DRV_SPI_DMA_TXFER_SIZE);
            void * spiPtr = PLIB_SPI_BufferAddressGet(pDrvInstance->spiId);
            SYS_DMA_ChannelTransferAdd(pDrvInstance->txDmaChannelHandle, ptr, len, spiPtr, 1, 1);
            currentJob->txDMAProgressStage = DRV_SPI_DMA_DATA_INPROGRESS;
            currentJob->dataLeftToTx -= len;
            currentJob->dataTxed += len;
    }
    else
    {
        // Job is done
        currentJob->txDMAProgressStage = DRV_SPI_DMA_COMPLETE;
    }
}