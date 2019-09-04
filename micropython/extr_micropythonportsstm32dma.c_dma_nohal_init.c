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
typedef  int uint32_t ;
struct TYPE_5__ {int sub_instance; TYPE_3__* init; int /*<<< orphan*/  id; TYPE_2__* instance; } ;
typedef  TYPE_1__ dma_descr_t ;
struct TYPE_7__ {int MemBurst; int PeriphBurst; int Priority; int MemInc; int PeriphInc; int FIFOMode; int FIFOThreshold; } ;
struct TYPE_6__ {int CR; int FCR; } ;
typedef  TYPE_2__ DMA_Stream_TypeDef ;
typedef  TYPE_3__ DMA_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  dma_enable_clock (int /*<<< orphan*/ ) ; 

void dma_nohal_init(const dma_descr_t *descr, uint32_t config) {
    DMA_Stream_TypeDef *dma = descr->instance;

    // Enable the DMA peripheral
    dma_enable_clock(descr->id);

    // Set main configuration register
    const DMA_InitTypeDef *init = descr->init;
    dma->CR =
        descr->sub_instance         // CHSEL
        | init->MemBurst            // MBURST
        | init->PeriphBurst         // PBURST
        | init->Priority            // PL
        | init->MemInc              // MINC
        | init->PeriphInc           // PINC
        | config                    // MSIZE | PSIZE | CIRC | DIR
        ;

    // Set FIFO control register
    dma->FCR =
        init->FIFOMode              // DMDIS
        | init->FIFOThreshold       // FTH
        ;
}