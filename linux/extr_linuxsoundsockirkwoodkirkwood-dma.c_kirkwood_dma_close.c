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
struct snd_pcm_substream {scalar_t__ stream; } ;
struct kirkwood_dma_data {int /*<<< orphan*/  irq; scalar_t__ io; int /*<<< orphan*/ * substream_rec; int /*<<< orphan*/ * substream_play; } ;

/* Variables and functions */
 scalar_t__ KIRKWOOD_ERR_MASK ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct kirkwood_dma_data*) ; 
 struct kirkwood_dma_data* kirkwood_priv (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int kirkwood_dma_close(struct snd_pcm_substream *substream)
{
	struct kirkwood_dma_data *priv = kirkwood_priv(substream);

	if (!priv)
		return 0;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		priv->substream_play = NULL;
	else
		priv->substream_rec = NULL;

	if (!priv->substream_play && !priv->substream_rec) {
		writel(0, priv->io + KIRKWOOD_ERR_MASK);
		free_irq(priv->irq, priv);
	}

	return 0;
}