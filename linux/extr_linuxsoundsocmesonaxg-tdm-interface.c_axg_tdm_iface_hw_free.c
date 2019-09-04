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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct axg_tdm_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  axg_tdm_stream_stop (struct axg_tdm_stream*) ; 
 struct axg_tdm_stream* snd_soc_dai_get_dma_data (struct snd_soc_dai*,struct snd_pcm_substream*) ; 

__attribute__((used)) static int axg_tdm_iface_hw_free(struct snd_pcm_substream *substream,
				 struct snd_soc_dai *dai)
{
	struct axg_tdm_stream *ts = snd_soc_dai_get_dma_data(dai, substream);

	/* Stop all attached formatters */
	axg_tdm_stream_stop(ts);

	return 0;
}