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
struct snd_soc_dai {int /*<<< orphan*/ * capture_dma_data; } ;
struct rk_pdm_dev {int /*<<< orphan*/  capture_dma_data; } ;

/* Variables and functions */
 struct rk_pdm_dev* to_info (struct snd_soc_dai*) ; 

__attribute__((used)) static int rockchip_pdm_dai_probe(struct snd_soc_dai *dai)
{
	struct rk_pdm_dev *pdm = to_info(dai);

	dai->capture_dma_data = &pdm->capture_dma_data;

	return 0;
}