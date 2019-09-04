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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct atiixp_modem {int /*<<< orphan*/ * ac97; } ;
struct atiixp_dma {int /*<<< orphan*/  buf_bytes; int /*<<< orphan*/  buf_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_addr; struct atiixp_dma* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_LINE1_LEVEL ; 
 int /*<<< orphan*/  AC97_LINE1_RATE ; 
 int NUM_ATI_CODECS ; 
 int atiixp_build_dma_packets (struct atiixp_modem*,struct atiixp_dma*,struct snd_pcm_substream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_period_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_periods (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_ac97_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct atiixp_modem* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_atiixp_pcm_hw_params(struct snd_pcm_substream *substream,
				   struct snd_pcm_hw_params *hw_params)
{
	struct atiixp_modem *chip = snd_pcm_substream_chip(substream);
	struct atiixp_dma *dma = substream->runtime->private_data;
	int err;
	int i;

	err = snd_pcm_lib_malloc_pages(substream, params_buffer_bytes(hw_params));
	if (err < 0)
		return err;
	dma->buf_addr = substream->runtime->dma_addr;
	dma->buf_bytes = params_buffer_bytes(hw_params);

	err = atiixp_build_dma_packets(chip, dma, substream,
				       params_periods(hw_params),
				       params_period_bytes(hw_params));
	if (err < 0)
		return err;

	/* set up modem rate */
	for (i = 0; i < NUM_ATI_CODECS; i++) {
		if (! chip->ac97[i])
			continue;
		snd_ac97_write(chip->ac97[i], AC97_LINE1_RATE, params_rate(hw_params));
		snd_ac97_write(chip->ac97[i], AC97_LINE1_LEVEL, 0);
	}

	return err;
}