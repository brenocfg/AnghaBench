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
struct stm32_spdifrx_data {scalar_t__ dmab; scalar_t__ ctrl_chan; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 struct stm32_spdifrx_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  snd_dma_free_pages (scalar_t__) ; 

__attribute__((used)) static int stm32_spdifrx_remove(struct platform_device *pdev)
{
	struct stm32_spdifrx_data *spdifrx = platform_get_drvdata(pdev);

	if (spdifrx->ctrl_chan)
		dma_release_channel(spdifrx->ctrl_chan);

	if (spdifrx->dmab)
		snd_dma_free_pages(spdifrx->dmab);

	return 0;
}