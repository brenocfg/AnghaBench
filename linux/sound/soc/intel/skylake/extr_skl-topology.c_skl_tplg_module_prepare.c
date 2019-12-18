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
struct snd_soc_dapm_widget {int dummy; } ;
struct skl_pipe {int /*<<< orphan*/  p_params; } ;
struct skl_module_cfg {int dev_type; } ;
struct skl_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  SKL_DEVICE_HDAHOST 129 
#define  SKL_DEVICE_HDALINK 128 
 int skl_pcm_host_dma_prepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int skl_pcm_link_dma_prepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skl_tplg_module_prepare(struct skl_dev *skl, struct skl_pipe *pipe,
		struct snd_soc_dapm_widget *w, struct skl_module_cfg *mcfg)
{
	switch (mcfg->dev_type) {
	case SKL_DEVICE_HDAHOST:
		return skl_pcm_host_dma_prepare(skl->dev, pipe->p_params);

	case SKL_DEVICE_HDALINK:
		return skl_pcm_link_dma_prepare(skl->dev, pipe->p_params);
	}

	return 0;
}