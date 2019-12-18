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
typedef  scalar_t__ dma_id_t ;
struct TYPE_2__ {int* counter; } ;

/* Variables and functions */
 scalar_t__ NSTREAMS_PER_CONTROLLER ; 
 int /*<<< orphan*/  SYSTICK_DISPATCH_DMA ; 
 TYPE_1__ dma_idle ; 
 int /*<<< orphan*/  dma_idle_handler ; 
 int /*<<< orphan*/  systick_enable_dispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dma_tickle(dma_id_t dma_id) {
    dma_idle.counter[(dma_id < NSTREAMS_PER_CONTROLLER) ? 0 : 1] = 1;
    systick_enable_dispatch(SYSTICK_DISPATCH_DMA, dma_idle_handler);
}