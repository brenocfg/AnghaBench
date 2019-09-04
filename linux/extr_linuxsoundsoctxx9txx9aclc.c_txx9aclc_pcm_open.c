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
struct txx9aclc_soc_device {struct txx9aclc_dmadata* dmadata; } ;
struct txx9aclc_dmadata {int dummy; } ;
struct snd_pcm_substream {size_t stream; TYPE_1__* runtime; } ;
struct TYPE_2__ {struct txx9aclc_dmadata* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 int snd_pcm_hw_constraint_integer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int snd_soc_set_runtime_hwparams (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txx9aclc_pcm_hardware ; 
 struct txx9aclc_soc_device txx9aclc_soc_device ; 

__attribute__((used)) static int txx9aclc_pcm_open(struct snd_pcm_substream *substream)
{
	struct txx9aclc_soc_device *dev = &txx9aclc_soc_device;
	struct txx9aclc_dmadata *dmadata = &dev->dmadata[substream->stream];
	int ret;

	ret = snd_soc_set_runtime_hwparams(substream, &txx9aclc_pcm_hardware);
	if (ret)
		return ret;
	/* ensure that buffer size is a multiple of period size */
	ret = snd_pcm_hw_constraint_integer(substream->runtime,
					    SNDRV_PCM_HW_PARAM_PERIODS);
	if (ret < 0)
		return ret;
	substream->runtime->private_data = dmadata;
	return 0;
}