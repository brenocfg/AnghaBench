#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t dma_id_t ;
struct TYPE_3__ {size_t id; int /*<<< orphan*/  sub_instance; } ;
typedef  TYPE_1__ dma_descr_t ;

/* Variables and functions */
 int DMA_INVALID_CHANNEL ; 
 int DMA_SUB_INSTANCE_AS_UINT8 (int /*<<< orphan*/ ) ; 
 int* dma_last_sub_instance ; 

void dma_invalidate_channel(const dma_descr_t *dma_descr) {
    if (dma_descr != NULL) {
        dma_id_t dma_id = dma_descr->id;
        // Only compare the sub-instance, not the direction bit (MSB)
        if ((dma_last_sub_instance[dma_id] & 0x7f) == DMA_SUB_INSTANCE_AS_UINT8(dma_descr->sub_instance) ) {
            dma_last_sub_instance[dma_id] = DMA_INVALID_CHANNEL;
        }
    }
}