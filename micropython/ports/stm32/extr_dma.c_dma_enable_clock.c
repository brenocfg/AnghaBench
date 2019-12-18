#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  mp_uint_t ;
typedef  int dma_id_t ;

/* Variables and functions */
 int DMA1_ENABLE_MASK ; 
 int /*<<< orphan*/  DMA1_IS_CLK_ENABLED () ; 
 int DMA2_ENABLE_MASK ; 
 int /*<<< orphan*/  DMA2_IS_CLK_ENABLED () ; 
 int /*<<< orphan*/  DMA_INVALID_CHANNEL ; 
 int /*<<< orphan*/  MICROPY_BEGIN_ATOMIC_SECTION () ; 
 int /*<<< orphan*/  MICROPY_END_ATOMIC_SECTION (int /*<<< orphan*/ ) ; 
 int NSTREAM ; 
 int NSTREAMS_PER_CONTROLLER ; 
 int /*<<< orphan*/  __HAL_RCC_DMA1_CLK_ENABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_DMA2_CLK_ENABLE () ; 
 int dma_enable_mask ; 
 int /*<<< orphan*/ * dma_last_sub_instance ; 

__attribute__((used)) static void dma_enable_clock(dma_id_t dma_id) {
    // We don't want dma_tick_handler() to turn off the clock right after we
    // enable it, so we need to mark the channel in use in an atomic fashion.
    mp_uint_t irq_state = MICROPY_BEGIN_ATOMIC_SECTION();
    uint32_t old_enable_mask = dma_enable_mask;
    dma_enable_mask |= (1 << dma_id);
    MICROPY_END_ATOMIC_SECTION(irq_state);

    if (dma_id < NSTREAMS_PER_CONTROLLER) {
        if (((old_enable_mask & DMA1_ENABLE_MASK) == 0) && !DMA1_IS_CLK_ENABLED()) {
            __HAL_RCC_DMA1_CLK_ENABLE();

            // We just turned on the clock. This means that anything stored
            // in dma_last_channel (for DMA1) needs to be invalidated.

            for (int channel = 0; channel < NSTREAMS_PER_CONTROLLER; channel++) {
                dma_last_sub_instance[channel] = DMA_INVALID_CHANNEL;
            }
        }
    }
    #if defined(DMA2)
    else {
        if (((old_enable_mask & DMA2_ENABLE_MASK) == 0) && !DMA2_IS_CLK_ENABLED()) {
            __HAL_RCC_DMA2_CLK_ENABLE();

            // We just turned on the clock. This means that anything stored
            // in dma_last_channel (for DMA2) needs to be invalidated.

            for (int channel = NSTREAMS_PER_CONTROLLER; channel < NSTREAM; channel++) {
                dma_last_sub_instance[channel] = DMA_INVALID_CHANNEL;
            }
        }
    }
    #endif
}