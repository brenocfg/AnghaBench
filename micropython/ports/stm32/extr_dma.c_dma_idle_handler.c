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
typedef  int uint32_t ;
struct TYPE_2__ {scalar_t__* counter; } ;

/* Variables and functions */
#define  DMA1_ENABLE_MASK 129 
#define  DMA2_ENABLE_MASK 128 
 int /*<<< orphan*/  DMA_IDLE_ENABLED () ; 
 int /*<<< orphan*/  DMA_IDLE_TICK (int) ; 
 scalar_t__ DMA_IDLE_TICK_MAX ; 
 int DMA_SYSTICK_LOG2 ; 
 int /*<<< orphan*/  __HAL_RCC_DMA1_CLK_DISABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_DMA2_CLK_DISABLE () ; 
 int const dma_enable_mask ; 
 TYPE_1__ dma_idle ; 

__attribute__((used)) static void dma_idle_handler(uint32_t tick) {
    if (!DMA_IDLE_ENABLED() || !DMA_IDLE_TICK(tick)) {
        return;
    }

    static const uint32_t   controller_mask[] = {
        DMA1_ENABLE_MASK,
        #if defined(DMA2)
        DMA2_ENABLE_MASK,
        #endif
    };
    {
        int controller = (tick >> DMA_SYSTICK_LOG2) & 1;
        if (dma_idle.counter[controller] == 0) {
            return;
        }
        if (++dma_idle.counter[controller] > DMA_IDLE_TICK_MAX) {
            if ((dma_enable_mask & controller_mask[controller]) == 0) {
                // Nothing is active and we've reached our idle timeout,
                // Now we'll really disable the clock.
                dma_idle.counter[controller] = 0;
                if (controller == 0) {
                    __HAL_RCC_DMA1_CLK_DISABLE();
                }
                #if defined(DMA2)
                else {
                    __HAL_RCC_DMA2_CLK_DISABLE();
                }
                #endif
            } else {
                // Something is still active, but the counter never got
                // reset, so we'll reset the counter here.
                dma_idle.counter[controller] = 1;
            }
        }
    }
}