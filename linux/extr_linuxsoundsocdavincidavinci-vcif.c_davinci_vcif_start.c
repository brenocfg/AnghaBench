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
typedef  int /*<<< orphan*/  u32 ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; } ;
struct davinci_vcif_dev {struct davinci_vc* davinci_vc; } ;
struct davinci_vc {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ DAVINCI_VC_CTRL ; 
 int /*<<< orphan*/  DAVINCI_VC_CTRL_RSTADC ; 
 int /*<<< orphan*/  DAVINCI_VC_CTRL_RSTDAC ; 
 int /*<<< orphan*/  MOD_REG_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct davinci_vcif_dev* snd_soc_dai_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void davinci_vcif_start(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct davinci_vcif_dev *davinci_vcif_dev =
			snd_soc_dai_get_drvdata(rtd->cpu_dai);
	struct davinci_vc *davinci_vc = davinci_vcif_dev->davinci_vc;
	u32 w;

	/* Start the sample generator and enable transmitter/receiver */
	w = readl(davinci_vc->base + DAVINCI_VC_CTRL);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		MOD_REG_BIT(w, DAVINCI_VC_CTRL_RSTDAC, 0);
	else
		MOD_REG_BIT(w, DAVINCI_VC_CTRL_RSTADC, 0);

	writel(w, davinci_vc->base + DAVINCI_VC_CTRL);
}