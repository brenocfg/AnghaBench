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
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {TYPE_2__* instance; } ;
typedef  TYPE_1__ dma_descr_t ;
struct TYPE_5__ {int /*<<< orphan*/  CR; void* M0AR; void* PAR; int /*<<< orphan*/  NDTR; } ;
typedef  TYPE_2__ DMA_Stream_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_SxCR_DBM ; 
 int /*<<< orphan*/  DMA_SxCR_EN ; 

void dma_nohal_start(const dma_descr_t *descr, uint32_t src_addr, uint32_t dst_addr, uint16_t len) {
    DMA_Stream_TypeDef *dma = descr->instance;
    dma->CR &= ~DMA_SxCR_DBM;
    dma->NDTR = len;
    dma->PAR = dst_addr;
    dma->M0AR = src_addr;
    dma->CR |= DMA_SxCR_EN;
}