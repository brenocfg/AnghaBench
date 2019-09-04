#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* dma_cfg; } ;
struct TYPE_3__ {void* dma_cfg; } ;
struct ux500_msp {TYPE_2__ capture_dma_data; TYPE_1__ playback_dma_data; } ;
struct stedma40_chan_cfg {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct msp_i2s_platform_data {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ux500_msp_i2s_of_init_msp(struct platform_device *pdev,
				struct ux500_msp *msp,
				struct msp_i2s_platform_data **platform_data)
{
	struct msp_i2s_platform_data *pdata;

	*platform_data = devm_kzalloc(&pdev->dev,
				     sizeof(struct msp_i2s_platform_data),
				     GFP_KERNEL);
	pdata = *platform_data;
	if (!pdata)
		return -ENOMEM;

	msp->playback_dma_data.dma_cfg = devm_kzalloc(&pdev->dev,
					sizeof(struct stedma40_chan_cfg),
					GFP_KERNEL);
	if (!msp->playback_dma_data.dma_cfg)
		return -ENOMEM;

	msp->capture_dma_data.dma_cfg = devm_kzalloc(&pdev->dev,
					sizeof(struct stedma40_chan_cfg),
					GFP_KERNEL);
	if (!msp->capture_dma_data.dma_cfg)
		return -ENOMEM;

	return 0;
}