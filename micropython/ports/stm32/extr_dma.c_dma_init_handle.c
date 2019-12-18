#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  sub_instance; TYPE_1__* init; int /*<<< orphan*/  instance; } ;
typedef  TYPE_2__ dma_descr_t ;
struct TYPE_6__ {int /*<<< orphan*/  Channel; int /*<<< orphan*/  Request; int /*<<< orphan*/  Direction; } ;
struct TYPE_8__ {void* Parent; TYPE_1__ Init; int /*<<< orphan*/  Instance; } ;
typedef  TYPE_3__ DMA_HandleTypeDef ;

/* Variables and functions */

void dma_init_handle(DMA_HandleTypeDef *dma, const dma_descr_t *dma_descr, uint32_t dir, void *data) {
    // initialise parameters
    dma->Instance = dma_descr->instance;
    dma->Init = *dma_descr->init;
    dma->Init.Direction = dir;
    #if defined(STM32L0) || defined(STM32L4) || defined(STM32H7)
    dma->Init.Request = dma_descr->sub_instance;
    #else
    #if !defined(STM32F0)
    dma->Init.Channel = dma_descr->sub_instance;
    #endif
    #endif
    // half of __HAL_LINKDMA(data, xxx, *dma)
    // caller must implement other half by doing: data->xxx = dma
    dma->Parent = data;
}