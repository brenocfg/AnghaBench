#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t dma_id_t ;
struct TYPE_11__ {size_t id; int /*<<< orphan*/  sub_instance; } ;
typedef  TYPE_1__ dma_descr_t ;
struct TYPE_12__ {scalar_t__ Instance; size_t ChannelIndex; int /*<<< orphan*/  DmaBaseAddress; int /*<<< orphan*/  State; } ;
typedef  TYPE_2__ DMA_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  DMA1 ; 
 int /*<<< orphan*/  DMA2 ; 
 scalar_t__ DMA2_Channel1 ; 
 int /*<<< orphan*/  DMA_PERIPH_TO_MEMORY ; 
 int DMA_SUB_INSTANCE_AS_UINT8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAL_DMA_DeInit (TYPE_2__*) ; 
 int /*<<< orphan*/  HAL_DMA_Init (TYPE_2__*) ; 
 int /*<<< orphan*/  HAL_DMA_STATE_READY ; 
 int /*<<< orphan*/  HAL_NVIC_EnableIRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_PRI_DMA ; 
 int /*<<< orphan*/  IRQn_NONNEG (int /*<<< orphan*/ ) ; 
 size_t NSTREAMS_PER_CONTROLLER ; 
 int /*<<< orphan*/  NVIC_SetPriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __HAL_DMA1_REMAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __HAL_DMA2_REMAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_enable_clock (size_t) ; 
 TYPE_2__** dma_handle ; 
 int /*<<< orphan*/  dma_init_handle (TYPE_2__*,TYPE_1__ const*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/ * dma_irqn ; 
 scalar_t__* dma_last_sub_instance ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void dma_init(DMA_HandleTypeDef *dma, const dma_descr_t *dma_descr, uint32_t dir, void *data){
    // Some drivers allocate the DMA_HandleTypeDef from the stack
    // (i.e. dac, i2c, spi) and for those cases we need to clear the
    // structure so we don't get random values from the stack)
    memset(dma, 0, sizeof(*dma));

    if (dma_descr != NULL) {
        dma_id_t dma_id  = dma_descr->id;

        dma_init_handle(dma, dma_descr, dir, data);
        // set global pointer for IRQ handler
        dma_handle[dma_id] = dma;

        dma_enable_clock(dma_id);

        #if defined(STM32H7) || defined(STM32L0) || defined(STM32L4)
        // Always reset and configure the H7 and L0/L4 DMA peripheral
        // (dma->State is set to HAL_DMA_STATE_RESET by memset above)
        // TODO: understand how L0/L4 DMA works so this is not needed
        HAL_DMA_DeInit(dma);
        HAL_DMA_Init(dma);
        NVIC_SetPriority(IRQn_NONNEG(dma_irqn[dma_id]), IRQ_PRI_DMA);
        #else
        // if this stream was previously configured for this channel/request and direction then we
        // can skip most of the initialisation
        uint8_t sub_inst = DMA_SUB_INSTANCE_AS_UINT8(dma_descr->sub_instance) | (dir == DMA_PERIPH_TO_MEMORY) << 7;
        if (dma_last_sub_instance[dma_id] != sub_inst) {
            dma_last_sub_instance[dma_id] = sub_inst;

            // reset and configure DMA peripheral
            // (dma->State is set to HAL_DMA_STATE_RESET by memset above)
            HAL_DMA_DeInit(dma);
            HAL_DMA_Init(dma);
            NVIC_SetPriority(IRQn_NONNEG(dma_irqn[dma_id]), IRQ_PRI_DMA);
            #if defined(STM32F0)
            if (dma->Instance < DMA2_Channel1) {
                __HAL_DMA1_REMAP(dma_descr->sub_instance);
            } else {
                __HAL_DMA2_REMAP(dma_descr->sub_instance);
            }
            #endif
        } else {
            // only necessary initialization
            dma->State = HAL_DMA_STATE_READY;
            #if defined(STM32F0)
            // These variables are used to access the relevant 4 bits in ISR and IFCR
            if (dma_id < NSTREAMS_PER_CONTROLLER) {
                dma->DmaBaseAddress = DMA1;
                dma->ChannelIndex = dma_id * 4;
            } else {
                dma->DmaBaseAddress = DMA2;
                dma->ChannelIndex = (dma_id - NSTREAMS_PER_CONTROLLER) * 4;
            }
            #elif defined(STM32F4) || defined(STM32F7)
            // calculate DMA base address and bitshift to be used in IRQ handler
            extern uint32_t DMA_CalcBaseAndBitshift(DMA_HandleTypeDef *hdma);
            DMA_CalcBaseAndBitshift(dma);
            #endif
        }
        #endif

        HAL_NVIC_EnableIRQ(dma_irqn[dma_id]);
    }
}