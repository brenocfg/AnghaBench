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
typedef  int u8 ;
struct snd_soc_pcm_runtime {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct rt5514_dsp {int /*<<< orphan*/  dma_lock; scalar_t__ dma_offset; struct snd_pcm_substream* substream; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  RT5514_IRQ_CTRL ; 
 int RT5514_IRQ_STATUS_BIT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  rt5514_schedule_copy (struct rt5514_dsp*) ; 
 int /*<<< orphan*/  rt5514_spi_burst_read (int /*<<< orphan*/ ,int*,int) ; 
 int snd_pcm_lib_alloc_vmalloc_buffer (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct rt5514_dsp* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5514_spi_hw_params(struct snd_pcm_substream *substream,
			       struct snd_pcm_hw_params *hw_params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct rt5514_dsp *rt5514_dsp =
		snd_soc_component_get_drvdata(component);
	int ret;
	u8 buf[8];

	mutex_lock(&rt5514_dsp->dma_lock);
	ret = snd_pcm_lib_alloc_vmalloc_buffer(substream,
			params_buffer_bytes(hw_params));
	rt5514_dsp->substream = substream;
	rt5514_dsp->dma_offset = 0;

	/* Read IRQ status and schedule copy accordingly. */
	rt5514_spi_burst_read(RT5514_IRQ_CTRL, (u8 *)&buf, sizeof(buf));
	if (buf[0] & RT5514_IRQ_STATUS_BIT)
		rt5514_schedule_copy(rt5514_dsp);

	mutex_unlock(&rt5514_dsp->dma_lock);

	return ret;
}