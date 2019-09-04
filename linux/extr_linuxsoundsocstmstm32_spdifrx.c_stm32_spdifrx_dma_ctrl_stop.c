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
struct stm32_spdifrx_data {int /*<<< orphan*/  ctrl_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmaengine_terminate_async (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stm32_spdifrx_dma_ctrl_stop(struct stm32_spdifrx_data *spdifrx)
{
	dmaengine_terminate_async(spdifrx->ctrl_chan);
}