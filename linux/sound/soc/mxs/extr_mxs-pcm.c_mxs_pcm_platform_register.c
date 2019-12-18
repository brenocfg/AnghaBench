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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_DMAENGINE_PCM_FLAG_HALF_DUPLEX ; 
 int devm_snd_dmaengine_pcm_register (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxs_dmaengine_pcm_config ; 

int mxs_pcm_platform_register(struct device *dev)
{
	return devm_snd_dmaengine_pcm_register(dev, &mxs_dmaengine_pcm_config,
		SND_DMAENGINE_PCM_FLAG_HALF_DUPLEX);
}