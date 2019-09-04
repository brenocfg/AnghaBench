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
typedef  int dma_id_t ;

/* Variables and functions */
 int dma_enable_mask ; 
 int /*<<< orphan*/  dma_tickle (int) ; 

__attribute__((used)) static void dma_disable_clock(dma_id_t dma_id) {
    // We just mark the clock as disabled here, but we don't actually disable it.
    // We wait for the timer to expire first, which means that back-to-back
    // transfers don't have to initialize as much.
    dma_tickle(dma_id);
    dma_enable_mask &= ~(1 << dma_id);
}