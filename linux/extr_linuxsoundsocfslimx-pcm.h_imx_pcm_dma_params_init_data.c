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
struct imx_dma_data {int dma_request; int peripheral_type; int /*<<< orphan*/  priority; } ;
typedef  enum sdma_peripheral_type { ____Placeholder_sdma_peripheral_type } sdma_peripheral_type ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_PRIO_HIGH ; 

__attribute__((used)) static inline void
imx_pcm_dma_params_init_data(struct imx_dma_data *dma_data,
	int dma, enum sdma_peripheral_type peripheral_type)
{
	dma_data->dma_request = dma;
	dma_data->priority = DMA_PRIO_HIGH;
	dma_data->peripheral_type = peripheral_type;
}