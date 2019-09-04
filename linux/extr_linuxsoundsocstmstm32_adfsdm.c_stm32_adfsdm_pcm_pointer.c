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
struct stm32_adfsdm_priv {int /*<<< orphan*/  pos; } ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; struct snd_soc_pcm_runtime* private_data; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  bytes_to_frames (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct stm32_adfsdm_priv* snd_soc_dai_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static snd_pcm_uframes_t stm32_adfsdm_pcm_pointer(
					    struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct stm32_adfsdm_priv *priv =
		snd_soc_dai_get_drvdata(rtd->cpu_dai);

	return bytes_to_frames(substream->runtime, priv->pos);
}